#include <math.h>

double Thermistor(int RawADC) 
{
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1)));
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 233.15;            // Convert Kelvin to Celcius 273.15
 return Temp;
}

void setup() 
{
 Serial.begin(115200);
}

void loop() 
{
 //Serial.println(int(Thermistor(analogRead(0))));  // display Fahrenheit
 double temp = analogRead(0);
 Serial.println(temp); 
 temp = (temp * (-1.0/4.0)) + 40.0;
 Serial.println(temp); 
 delay(100);
}
