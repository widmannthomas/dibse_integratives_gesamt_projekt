#include <ESP8266WiFi.h>
#include <Pinger.h>
#include <lwip/icmp.h>
#include "user_interface.h"

#ifndef STASSID
#define STASSID "****"
#define STAPSK  "****"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

Pinger pinger;

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
}

void setup() 
{
  WiFi.mode(WIFI_STA); 
  Serial.begin(115200);
  Serial.println("Connect to: " + String(ssid));

  uint8_t mac[6];
  generateRandomMac(mac);
  wifi_set_macaddr(STATION_IF, const_cast<uint8*>(mac));
  Serial.print("MAC address is ");
  Serial.println(WiFi.macAddress());

  connectToWiFi();

  pinger.OnReceive([](const PingerResponse& response)
  {
    if (response.ReceivedResponse)
    {
      Serial.printf(
        "Reply from %s: bytes=%d time=%lums TTL=%d\n",
        response.DestIPAddress.toString().c_str(),
        response.EchoMessageSize - sizeof(struct icmp_echo_hdr),
        response.ResponseTime,
        response.TimeToLive);
    }
    else
    {
      Serial.printf("Request timed out.\n");
    }

    // Return true to continue the ping sequence.
    // If current event returns false, the ping sequence is interrupted.
    return true;
  });

  pinger.Ping(WiFi.gatewayIP(), 1000);

  wifi_set_sleep_type(LIGHT_SLEEP_T);
}

short ctn = 0;
void loop() 
{
  //lightSleep(5000);
  Serial.println("WiFi status: " + String(WiFi.status()) + " connected: " + String(WL_CONNECTED));

  Serial.println(millis());

  delay(1000);

  //connectToWiFi();
  //sendSensorData();
}
