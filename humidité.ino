//============Configuration du senior el system============
unsigned long set_moist = 2; //Réglage de l'humidité du sol requise par la plante remplacer les X par la valeur
bool set_night = 1; //paramètre de prise en compte de la nuit, true si la nuit est prise en compte
//=========================================================
bool night=0; //il fait nuit ou pas?, true si il fait nuit 
unsigned long press=0; //valeur de la pression atmo
unsigned long press_save=0; //Sauvegarde de la pression pour la prise d'info initiale (avant les 3h)
bool wat_lvl_crit=0; //valeur booléenne, true si niveau de l'eau est faible
bool start_water = 0; //variable qui controle l'arrosage
unsigned long temps=0; //timer (max 49d)
unsigned long temps_save=0; //Sauvegarde de l'état précédent du chrono pour faire un timer
int br_nuit = 13; //broche détect. nuit
int br_lvl_eau = 12; //broche détect. lvl eau
int br_soil_moist = 11; //broche détect. soil moist 
int br_press = 10; //broche détect. de la press atmo
int br_start_water = 1; //broche électrovanne
int br_led_wat_low = 2;
enum {read_sensors, check_rain, begin_water, low_water}state;

void setup(){
//=======Init pins=======
  pinMode(br_start_water, OUTPUT);
  pinMode(br_nuit, INPUT_PULLUP);
  pinMode(br_lvl_eau, INPUT);
  pinMode(br_soil_moist, INPUT);
  pinMode(br_press, INPUT);
  pinMode(br_led_wat_low, OUTPUT);
  digitalWrite(br_start_water, LOW);
  digitalWrite(br_led_wat_low, LOW);
//=======Init var=======
  temps = millis();
  temps_save = 0;
  night = 0;
  wat_lvl_crit = 0;
  start_water = 0;
  press_save = digitalRead(br_press);
}

void loop() {
  switch(state){
    case read_sensors:
      digitalWrite(br_start_water, LOW); //couper l'arrosage
      night = digitalRead(br_nuit); //a remplacer par un script photo résistance (avec quantum comme potentiomètre)
      if (digitalRead(br_lvl_eau) == HIGH) { //s'assurer que le niveau d'eau est correct 
        state = low_water;
      if (night == 1) {
//        if (digitalRead(br_soil_moist) < set_moist) { //vérifier que la terre est moins humide que défini par l'utilisateur
          if (digitalRead(br_soil_moist) == HIGH) {
        	state = check_rain ;
        } 
      } 
      } else {
          state=read_sensors;
        }
    	break;
    case check_rain:
      if (temps_save + 10800 < millis()) { //décompte des 3h
        press_save = digitalRead(br_press);
   } if (digitalRead(br_press)<(press_save - 5)) { //Baisse de 5 hpa constatée
        state = begin_water; //Switch vers la partie de code qui controle l'électrovanne
   }  else {
        state = read_sensors;
      }
    	break;
    case begin_water:
      digitalWrite(br_start_water, HIGH);
      start_water = 1;
      delay(1800);
      state=read_sensors;
    	break;
    case low_water:
      while (digitalRead(br_start_water) == HIGH) {
        digitalWrite(br_led_wat_low, HIGH);
   }  state = read_sensors;
    	break;
  }
}
