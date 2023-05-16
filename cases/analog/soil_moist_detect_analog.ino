void setup() {
  pinMode(3, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int anaread = analogRead(A0);
  int lum = map(anaread, 0, 1023, 0, 255);
  Serial.print("anaread: ");
  Serial.println(anaread);
  Serial.print("lum: ");
  Serial.println(lum);
  analogWrite(3,lum);
}
