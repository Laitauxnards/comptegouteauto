void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int percent = map(analogRead(0), 500, 250, 0, 100);
  Serial.print("Pourcentage d'humidité : ");
  Serial.println(percent);
}
