#include <math.h>

double thermistorCelcius(int rawADC) // http://playground.arduino.cc/ComponentLib/Thermistor2
{
 return 0;
}

void setup() 
{
 Serial.begin(115200);
}

void loop() 
{
 //Serial.println(int(thermistorCelcius(analogRead(0))));
 double temp = analogRead(0);
 Serial.println(temp); 
 temp = (temp * (-1.0/4.0)) + 40.0; // hack solution just to get a result that SEEMS agreeable
 Serial.println(temp); 
 delay(100);
}
