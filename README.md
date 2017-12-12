# IoT Sensor
Arduino project with Wi-Fi and a temperature sensor

https://www.youtube.com/watch?v=PSczkB4wYec

https://learn.sparkfun.com/tutorials/esp8266-wifi-shield-hookup-guide
1. Go to the Arduino IDE
2. Copy this link: http://arduino.esp8266.com/versions/2.3.0/package_esp8266com_index.json
3. Paste it in File>Prefererences in the field for `Additional Boards Manager URLs:`
4. Go to Boards Manager and install esp8266
5. Go to Boards and select ESPino

- Wi-Fi module
  * ESP8266MOD
  * ADC : Analog to Digital Converter
  * Uses 3.3V which means that you will need level convertion when using it with an Arduino which uses 5V
  
  http://rancidbacon.com/files/kiwicon8/ESP8266_WiFi_Module_Quick_Start_Guide_v_1.0.4.pdf
  
  
  - Building ESP Client
   1. https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiClient/WiFiClient.ino
   
  
