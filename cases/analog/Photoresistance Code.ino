#define PHORORESISTOR_PIN A1

void setup(){
    pinMode(A2, INPUT);
    Serial.begin(9600);
}

void loop(){
    Serial.print("lum: ");
    Serial.println(analogRead(A2));
    delay(500);
}
