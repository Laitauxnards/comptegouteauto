#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  


void setup(){
    lcd.begin(16, 2);
    pinMode(A1, INPUT);
    Serial.begin(9600);
}

void loop(){
    lcd.setCursor(0, 0);  
    int percent = map(analogRead(1), 509, 247, 0, 100);
    lcd.print("% hum: ");
    lcd.print(percent);
    lcd.setCursor(0, 1);
    lcd.print(analogRead(1));
    delay(50);
}
