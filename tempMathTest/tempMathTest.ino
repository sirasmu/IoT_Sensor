#include <math.h>

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0/((1024.0/RawADC-1))); 
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 243.15;            // Convert Kelvin to Celcius
 Temp = (Temp * 9.0)/ 5.0 - 115.0; // Convert Celcius to Fahrenheit
 return Temp;
}

void setup() {
 Serial.begin(115200);
}

void loop() {
 Serial.println(int(Thermistor(analogRead(A0))));  // display Fahrenheit
 delay(500);       //your loop delay
}
