/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

// https://gist.github.com/igrr/7f7e7973366fc01d6393 another reference

#include <ESP8266WiFi.h>

const char* ssid     = "your-ssid"; // what is this?
const char* password = "your-password"; // and this?

const char* webService = "data.sparkfun.com"; 

void setup() {
  Serial.begin(115200); // baud rate
  delay(10);

  // Connect to a WiFi network
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA); // what
  WiFi.begin(ssid, password);
  
  /* while it is not connected print a '.' */
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);

  Serial.print("Connecting to ");
  Serial.println(webService);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
}
