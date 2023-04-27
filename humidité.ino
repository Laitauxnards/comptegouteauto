//============Configuration du senior el system============
unsigned float set_moist = XXXX; //Réglage de l'humidité du sol requise par la plante remplacer les X par la valeur
bool set_night = True; //paramètre de prise en compte de la nuit, true si la nuit est prise en compte
//=========================================================
bool night; //il fait nuit ou pas?, true si il fait nuit 
unsigned float press; //valeur de la pression atmo
unsigned float press_save; //Sauvegarde de la pression pour la prise d'info initiale (avant les 3h)
bool wat_lvl_crit; //valeur booléenne, true si niveau de l'eau est faible
bool start_water; //variable qui controle l'arrosage
unsigned long temps; //timer (max 49d)
unsigned long temps_save; //Sauvegarde de l'état précédent du chrono pour faire un timer
int br_nuit = 13; //broche détect. nuit
int br_lvl_eau = 12; //broche détect. lvl eau
int br_soil_moist = 11; //broche détect. soil moist 
int br_press = 10; //broche détect. de la press atmo
int br_start_water = 1; //broche électrovanne
int br_led_wat_low = 2
enum {read_sensors, check_rain, begin_water, low_water} state;

void setup()
{
//=======Init pins=======
  pinMode(br_start_water, OUTPUT);
  pinMode(br_nuit, INPUT_PULLUP);
  pinMode(br_lvl_eau, INPUT);
  pinMode(br_soil_moist, INPUT);
  pinMode(br_press, INPUT);
  pinMode(br_led_wat_low, OUPUT);
  digitalWrite(br_start_water, LOW);
  digitalWrite(br_led_wat_low, LOW);
//=======Init var=======
  temps = millis();
  temps_save = 0;
  moist = 0;
  night = False;
  wat_lvl_crit = False;
  start_water = False;
  press_save = digitalRead(br_press)
}

void loop() {
  switch(state){
    case read_sensors:
      digitalWrite(br_start_water, LOW); //couper l'arrosage
      night = digitalRead(br_nuit); //a remplacer par un script photo résistance (avec quantum comme potentiomètre)
      if digitalRead(br_lvl_eau) = HIGH { //vérifier que la terre est moins humide que défini par l'utilisateur 
        state = low_water;
      if night=True {
        if digitalRead(br_soil_moist) < set_moist { //s'assurer que le niveau d'eau est correct
          state = check_rain ;
        } 
      } 
      } else {
          state=read_sensors
        }
    case check_rain:
      if temps_save + 10800 < millis() { //dé;compte des 3h
        press_save = digitalRead(br_press)
   }  if digitalRead(br_press)<press_save - 5 { //Baisse de 5 hpa constatée
        stare = start_water; //Switch vers la partie de code qui controle l'électrovanne
   }  else {
        state = read_sensors
      }
    case start_water:
      digitalWrite(br_start_water, HIGH);
      

      
  }
}
