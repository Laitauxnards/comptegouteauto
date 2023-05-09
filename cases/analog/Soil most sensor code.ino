void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int anaread = analogRead(0);
  int percent = map(anaread, 500, 250, 0, 100);
  Serial.print("percent : ");
  Serial.println(percent);