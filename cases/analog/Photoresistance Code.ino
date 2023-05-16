int pr = A0;

void setup() {
 pinMode(lum, INPUT);
 Serial.begin(9600);
 } 

void loop() {
    Serial.print("lum: ");
    Serial.println(analogRead(pr));
}

