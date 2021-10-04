#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Set WiFi credentials
#define WIFI_SSID "***"
#define WIFI_PASS "***"
#define SERVER_IP "192.168.1.191"
#define TCP_PORT 63477
#define UDP_PORT 50262

// UDP
WiFiUDP UDP;

void setup() 
{
  // Setup serial port
  Serial.begin(115200);  
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
  }
}

void loop() 
{ 
  Serial.println("Send UDP.");

  unsigned long unTime = millis();

  /*
  UDP.beginPacket(SERVER_IP, UDP_PORT);
  for(short n = 0; n < 10000; n++)
  {
    UDP.write(n);
  }
  Serial.println("");
  UDP.endPacket();

  Serial.println("UDP took: " + String(millis() - unTime) + "ms");

  delay(2000);
  */
  

  unTime = millis();

  Serial.println("Send TCP.");
  WiFiClient client;
  client.connect(SERVER_IP, TCP_PORT);
  for(short n = 0; n < 5000; n++)
  {
    client.write(rand());
  }

  client.stop();
  Serial.println("");

  Serial.println("TCP took: " + String(millis() - unTime) + "ms");

  delay(2000);
}
