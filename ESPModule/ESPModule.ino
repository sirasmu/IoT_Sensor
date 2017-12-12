/*
  Name:    ESP8266Module.ino
  Created: 10/19/2017 7:16:40 PM
  Author:  Amavin
*/
#include "lwip/tcp_impl.h"

void tcpCleanup()
{
  while(tcp_tw_pcbs!=NULL)
  {
    tcp_abort(tcp_tw_pcbs);
  }
}
#include <ESP8266SSDP.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <limits.h>
#define TCP_PORT 3001
#define EOT 4

const char* ssid[4] = { "internet" };
const char* password[4] = { "PW"};

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(TCP_PORT);

void setup() {
  Serial.begin(38400);
  delay(10);
  /*IPAddress ip(192, 168, 1, 249);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress DNS(192, 168, 1, 1);
  WiFi.config(ip, gateway, subnet, DNS);*/
  delay(100);
  // Connect to WiFi network
  for (int i = 0; i < 4 ; i++)
  {
    printf("trying: %s with password: %s\n", ssid[i], password[i]);

    WiFi.begin(ssid[i], password[i]);
    unsigned long timeout = millis() + 45000; //45s timeout
    while (WiFi.status() != WL_CONNECTED && millis() < timeout) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println();
      Serial.print("Connected to: ");
      Serial.println(WiFi.SSID());
      break;
    }
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("wifi failed");
    return;
  }
  Serial.println();
  Serial.println("WiFi connected");


  // Print the IP address
  Serial.println(WiFi.localIP());

  // Start the TCP server
  server.begin();
  Serial.println("Server started");

  Serial.printf("Starting SSDP...\n");
  SSDP.setHTTPPort(TCP_PORT);
  SSDP.setDeviceType("upnp-dev:device:DistanceSensorWiFiClient");
  SSDP.setSerialNumber(ESP.getChipId());
  SSDP.begin();


  Serial.println("OK");
}
// the loop function runs over and over again until power down or reset
void loop()
{
  if (server.hasClient())
  {
    WiFiClient c = server.available();
    if (c && c.connected())
    {
      int bytes = c.available();
      unsigned long t = micros();
      while (micros() - t < 10000ul && !(bytes = c.available())) { } //wait up to 10ms for bytes to arrive
      //Serial.printf("d:1w:%d\n%c", micros() - t, EOT);
      if (bytes)
      {
        //pass along client's message
        byte buf[bytes + 1];
        c.readBytes(buf, bytes);
        buf[bytes] = EOT;
        Serial.write(buf, bytes+1);
        Serial.flush();

        //wait for response
        int b = 0;
        t = micros();
        while (micros() - t < 500000ul && !(b = Serial.available())) { } //waiting up to 500ms for resp
        //Serial.printf("d:2w:%d\n%c", micros() - t, EOT);
        //send response to client
        if (b)
        {
          t = micros();
          while (micros() - t < 500000ul)
          {
#define bufsize 1000
            byte c_buf[bufsize];
            size_t c_max = Serial.readBytesUntil(EOT, c_buf, bufsize);
            c.write((const uint8_t*)c_buf, c_max);
            if (c_max < bufsize)
              break; //Serial got End of Transmission; no more data available
            //c.printf("%s", readUntil(&Serial, EOT, 10000, 500000));
          }
          //Serial.printf("d:3w:%d\n%c", micros() - t, EOT);
          c.flush();
        }
      }
      //Serial.printf("Free: %d\n", ESP.getFreeHeap());
      tcpCleanup();
    }
  }
}
/*
char *readUntil(Stream *s, char delim, unsigned long max_bytes, unsigned long timeoutMicros)
{
#define bufsize 1000
    char *r = (char*)malloc(sizeof *r * bufsize);
    unsigned long chars_max = max_bytes;
    unsigned long current_chars_max = bufsize;
    unsigned long chars = 0;
    unsigned long t = micros();
    while (micros() - t < timeoutMicros && chars < ULONG_MAX)
    {
      byte t_b;
      while (chars < (current_chars_max - 1) && chars < chars_max)
      {
        while (s->available() <= 0 && micros() - t < timeoutMicros);
        if ((t_b = s->read()) < 0 || t_b == delim)
        {
          break;
        }
        *(r + chars++) = t_b;
      }
      if (chars < (current_chars_max - 1) && chars < chars_max)
        break; //Serial got End of Transmission; no more data available
      
      char *tmp = r;
      r = (char*)malloc(sizeof *r * (current_chars_max *= 2));
      memcpy(r, tmp, chars);
      free(tmp);
    }
    *(r + chars) = '\0';
    return r;
}*/



