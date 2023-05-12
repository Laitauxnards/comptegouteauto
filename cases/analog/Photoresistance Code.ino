int pr = A0;

void setup() {
 pinMode(pr, INPUT_PULLUP);
 Serial.begin(9600);
 } 

void loop() {
    Serial.print("pr: ");
    Serial.println(analogRead(pr));
}

