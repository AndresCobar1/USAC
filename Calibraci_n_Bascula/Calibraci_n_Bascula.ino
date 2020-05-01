#include "HX711.h"
 
byte pinData = 3;
byte pinClk = 2;
float x;
HX711 bascula;
 

float factor_calibracion = 20780.0;
 
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 programa de calibracion");
  Serial.println("+ para incrementar el factor de calibracion");
  Serial.println("- para disminuir el factor de calibracion");
 
  bascula.begin(pinData, pinClk);
  bascula.set_scale();
  bascula.tare();

  long zero_factor = bascula.read_average();

  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
}
 
void loop() {
 
  bascula.set_scale(factor_calibracion);
 
  Serial.print("Leyendo: ");
  x = bascula.get_units() * 2.20462;
  Serial.print(x, 1);
  Serial.print(" lbs");
  Serial.print(" factor_calibracion: ");
  Serial.print(factor_calibracion);
  Serial.println();
 
  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+')
      factor_calibracion += 10;
    else if (temp == '-')
      factor_calibracion -= 10;
  }
}
