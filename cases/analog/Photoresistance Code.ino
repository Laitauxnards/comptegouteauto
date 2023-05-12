int jsp = A0;

void setup() {
 pinMode(jsp, INPUT);
 } 

void loop() {
    Serial.print("jsp: ");
    Serial.println(analogRead(jsp));
}
