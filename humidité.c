int digitalPin = 4; // pour le relais
int analogPin = A0; // pour le capteur de l'humidité du sol
int digitalVal; // digital readings
int analogVal; //analog readings

void setup()
{
pinMode(digitalPin, OUTPUT);
digitalWrite(digitalPin, LOW);
}

void loop()
{
analogVal = analogRead(analogPin);//lire la valeur retournée par le capteur de l'humidité
if (analogVal<400){//si la capteur de l'humidité retourne une valeur<500
digitalWrite(digitalPin, HIGH);//La pompe à eau arrose la plante
} else { // sinon
digitalWrite(digitalPin, LOW);//La //La pompe à eau arrête l'arrosage
}
delay(100);
}
