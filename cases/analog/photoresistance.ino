void setup(){
 } 


void loop() {
   int state= analogRead(A0);
    Serial.print("State: ");
    Serial.println(state);
}
