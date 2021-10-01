#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "WIDMANN_PRIVATE"
#define STAPSK  "Wid2017_AP"
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
}

short ctn = 0;
void loop() 
{
  yield();
  delay(10);

  if(ctn == 100)
  {
    Serial.println("Keep alive.");
    ctn = 0;
  }

  ctn++;
}
