#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "user_interface.h"

#ifndef STASSID
#define STASSID "***"
#define STAPSK  "***"
#endif


#define MODEM_SLEEP
//#define LIGHT_SLEEP
//#define DEEP_SLEEP

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiClient espClient;
PubSubClient client(espClient);

void generateRandomMac(uint8_t mac[6])
{
  for (size_t i = 0; i < 6; ++i) 
  {
    mac[i] = random(256);
  }
  mac[0] = mac[0] & ~0x01;
}

void connectToWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer("192.168.1.43", 1883);

  String clientId = "DummyDevice-";
  clientId += String(WiFi.macAddress());
  if (client.connect(clientId.c_str())) 
  {
    Serial.println("connected");
  } 
  else 
  {
    Serial.print("failed, rc=");
    Serial.println(client.state());
  }
}

void publishData()
{
  Serial.println("Publish data...");
  client.publish("TEST_GROUP", "{\"temp\":23.4C}");
}

void setup() 
{
  WiFi.mode(WIFI_STA); 
  Serial.begin(115200);
  Serial.println("Connect to: " + String(ssid));

  //uint8_t mac[6];
  //generateRandomMac(mac);
  //wifi_set_macaddr(STATION_IF, const_cast<uint8*>(mac));
  Serial.print("MAC address is ");
  Serial.println(WiFi.macAddress());

  connectToWiFi();

#ifdef DEEP_SLEEP
  publishData();
  delay(100);
  ESP.deepSleep(900000000); //15min
#endif

#ifdef LIGHT_SLEEP
  wifi_set_sleep_type(LIGHT_SLEEP_T);
#endif
}

void loop() 
{
  publishData();
  delay(900000);
}
