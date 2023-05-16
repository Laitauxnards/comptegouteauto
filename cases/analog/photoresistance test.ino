#define PHORORESISTOR_PIN A1
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  


void setup(){
    lcd.begin(16, 2);
    pinMode(A1, INPUT);
    Serial.begin(9600);
}

void loop(){
    lcd.setCursor(0, 0);  
    lcd.print("lum: ");
    lcd.print(analogRead(A1));
    Serial.print("lum: ");
    Serial.println(analogRead(A1));
    delay(500);
}
