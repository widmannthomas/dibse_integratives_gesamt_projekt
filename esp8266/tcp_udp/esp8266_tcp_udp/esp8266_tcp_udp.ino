#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Set WiFi credentials
#define WIFI_SSID "***"
#define WIFI_PASS "***"
#define SERVER_IP "192.168.1.183"
#define TCP_PORT 63477
#define UDP_PORT 50262

#define PIN_CTRL 2

// UDP
WiFiUDP UDP;

void setup() 
{
  pinMode(PIN_CTRL, OUTPUT);
  digitalWrite(PIN_CTRL, LOW);
  
  // Setup serial port
  Serial.begin(115200);  
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
  }

  Serial.println(WiFi.localIP());
  delay(1000);
}

void loop() 
{ 
  Serial.println("Send UDP.");

  digitalWrite(PIN_CTRL, HIGH);

  unsigned long unTime = millis();

  
  UDP.beginPacket(SERVER_IP, UDP_PORT);
  for(short n = 0; n < 10000; n++)
  {
    UDP.write(n);
  }
  Serial.println("");
  UDP.endPacket();
  UDP.flush();

  delay(50);

  Serial.println("UDP took: " + String(millis() - unTime) + "ms");
  
  /*
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
  */

  digitalWrite(PIN_CTRL, LOW);

  delay(100);
}
