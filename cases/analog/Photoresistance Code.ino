#define PHORORESISTOR_PIN A1
#include <LiquidCrystal.h>

void setup(){
    pinMode(A1, INPUT);
    Serial.begin(9600);
}

void loop(){
    Serial.print("lum: ");
    Serial.println(analogRead(A1));
    delay(500);
}
