#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include "HX711.h"
#define CALIBRACION 32150.0
LiquidCrystal_I2C lcd(0x3f,16,2);
byte pinData = 3;
byte pinClk = 2;
int boton = 9 ;
int boton2 = 10;
bool estado = false ;
bool k, p;
bool estado1 = false;
HX711 bascula;

void setup() {
   pinMode( boton , INPUT_PULLUP) ;
    pinMode( boton2 , INPUT_PULLUP) ;
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Seleccione Peso");
    lcd.setCursor ( 0, 1 );
    lcd.print("25 <- - -> 35");
  Serial.begin(9600);
  bascula.begin(pinData, pinClk);
  bascula.set_scale(CALIBRACION);
  bascula.tare();
}

StaticJsonDocument<1000> doc;

void loop() {
lcd.display();

 bool  valor =  digitalRead(boton) ;    
 bool valor1= digitalRead(boton2);            
              if ( valor == true )  {
               k = true;
      
                }

                if(k == true){
              lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("Peso:");
             lcd.setCursor(0,1);
             lcd.print("25 lbs");
             float p = bascula.get_units();         
             float x = p * 2.20462;
             doc["peso"] = x;
             doc["hum"] = 1;
                 
             if(Serial.available()>=0)
              {
                serializeJson(doc, Serial);
                
              }
              delay(30000); // 30 detik
                             }
  if(valor1 == true){
    p = true;
   }
    if(p == true){
            lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("Peso:");
             lcd.setCursor(0,1);
             lcd.print("35 lbs");
             float p = bascula.get_units();
              float x = p * 2.20462;

              doc["peso"] = x;
              doc["hum"] = 1;
             
              if(Serial.available()>=0)
              {
                serializeJson(doc, Serial);
                
              }
              delay(30000); // 30 detik
              }
            }
