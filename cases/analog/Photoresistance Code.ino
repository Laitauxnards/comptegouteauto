int pr = A0;

void setup() {
 pinMode(pr, INPUT);
 } 

void loop() {
    Serial.print("pr: ");
    Serial.println(analogRead(pr));
}
