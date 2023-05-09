void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int anaread = analogRead(0);
  Serial.print("anaread: ");
  Serial.println(anaread);
}