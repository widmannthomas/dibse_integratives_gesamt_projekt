#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "****"
#define STAPSK  "****"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

void generateRandomMac(uint8_t mac[6])
{
  for (size_t i = 0; i < 6; ++i) 
  {
    mac[i] = random(256);
  }
  mac[0] = mac[0] & ~0x01;
}

void setup() 
{
  Serial.begin(115200);
  Serial.println("Connect to: " + String(ssid));

  uint8_t mac[6];
  generateRandomMac(mac);
  wifi_set_macaddr(STATION_IF, const_cast<uint8*>(mac));
  Serial.print("MAC address is ");
  Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    //Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Good night...");

  ESP.deepSleep(5E6);
}

void loop() {}
