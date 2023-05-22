//============Configuration du senior el system============
int set_moist = 50; //Réglage de l'humidité du sol requise par la plante remplacer les X par la valeur en % d'humidité (100% = terre très mouillée, 0% = terre sèche)
//=========================================================
//variables pour le timer et comparaison de la pression atmosphérique sur 3h
unsigned long press=0; //valeur de la pression atmo
unsigned long press_save=0; //Sauvegarde de la pression pour la prise d'info initiale (avant les 3h)
unsigned long temps=0; //timer (max 49d)
unsigned long temps_save=0; //Sauvegarde de l'état précédent du chrono pour faire un timer
//=========================================================
//Les variables suivantes ont été créées pour une identification plus facide de l'usage de chaque broche dans le programme
int br_nuit = A2; //broche de la photo résistance
int br_lvl_eau = 12; //broche du capteur à ultrasons pour le niveau de l'eau
int br_soil_moist = A1; //broche du capteur d'humidité du sol
int br_press = 10; //broche du baromètre
int br_start_water = 2; //broche électrovanne
int br_led_wat_low = 4; //broche faible niveau eau
//===========================================================
int percent_wat = 0; //valeur du pourcentage d'humidité du sol, valeur réelle (pas définie par l'utilisateur
enum {read_sensors, check_rain, begin_water, low_water}state; //enumération des différents états du système

void setup(){
  Serial.begin(9600); //démarrage de la liaison série qui ne sera utilisée que pour le débogage
  Serial.print("Initialized serial link... "); //logs pour débogage du programme
//=======Initialisation pins=======
  pinMode(br_start_water, OUTPUT);
  pinMode(br_nuit, INPUT);
  pinMode(br_lvl_eau, INPUT_PULLUP);
  pinMode(br_soil_moist, INPUT);
  pinMode(br_press, INPUT_PULLUP);
  pinMode(br_led_wat_low, OUTPUT);
  digitalWrite(br_start_water, LOW);
  digitalWrite(br_led_wat_low, LOW);
  Serial.print("Initialized pins... "); //logs pour débogage du programme
//=======Init variables=======
  temps = millis();
  temps_save = 0; //remise à 0 du timer
  press_save = digitalRead(br_press); //première lecture de la pression atmo (non terminé)
  state=read_sensors; //changement d'état du programme
  Serial.print("Initialized variables... "); //logs pour débogage du programme
}

void loop() {
  switch(state){
    case read_sensors: //début de l'état de lecture des capteurs
      digitalWrite(br_start_water, LOW); //couper l'arrosage
      //==========================
      percent_wat = (map(analogRead(A0), 520, 250, 0, 100)); //on assisgne à la variable percent_wat 
      //la valeur de la broche A0 mappée afin que 520 équivaux a 0% et 250, 100%. Ce afin d'avoir le pourcentage d'humidité du sol
     //===========================
      if (digitalRead(br_lvl_eau) == LOW) { //s'assurer que le niveau d'eau est correct 
        Serial.println("Low water ! Switching state to low_water"); //sortie débogage
        state = low_water; //on change d'état pour passer à "low_water"
        break; //on arrête l'execution de cet état pour skip vers l'état "low_water"
      }
      if (analogRead(br_nuit)<50) { //on vérifie qu'il fasse nuit avec la valeur analogique renvoyée par la photo résistance
        Serial.println("Night is true"); //sortie débogage
        if (percent_wat<set_moist) { //vérifier que la terre est moins humide que défini par l'utilisateur
          Serial.println("Soil is dry ! Switching state to check_rain");//sortie débogage
          state = check_rain;//on change d'état pour "check_rain"
        } 
      } else {
          Serial.println("Nothing detected, Switching state to read_sensors");//si aucune des conditions ci dessus n'est validée, on repars au début
          state=read_sensors;
        }
      //débogage
      Serial.println("Case read_sensors successfully executed using following settings: ");
      Serial.print("br_nuit: ");
      Serial.println(analogRead(br_nuit));
      Serial.print("br_lvl_eau: ");
      Serial.println(digitalRead(br_lvl_eau));
      Serial.print("br_soil_moist: ");
      Serial.print(percent_wat);
      Serial.println("%");
      Serial.print("br_soil_moist: ");
      Serial.println(analogRead(br_soil_moist));
      Serial.println("_________");
      //===========================
      delay(1000);//1 seconde de délais pour pouvoir lire les données de débogage
      break;//on arrête l'éxecution du programme et on passe à l'état suivant (peut être check_rain ou read_sensors)




    case check_rain: //début de l'état check_rain
      //Tout le code pour la vérification de si il va pleuvoir ou non n'a pas encore été créé. 
      //Nous en somme a la phase de création du code pour la photorésistance. Ce code va être complètement modifié.
      //Un début de code est disponible dans se repository à cette addresse https://github.com/l3ochan/comptegouteauto/blob/main/cases/analog/check_rain.ino
      //Le code n'a pas été modifié depuis longtemps et est très loin d'un stade final. Ne pas en tenir compte. 
      //Sachant tout ca, Pour le test de la machine d'état, la condition de pression atmosphérique était validée par l'activation d'un interrupteur.
      if (digitalRead(br_press)==LOW) { //interrupteur pression on?
        Serial.println("no pressure drop detected ! switching state to begin_water");//débogage
        state = begin_water; //interrupteur allumé, qui simule que la pression n'a pas baissé la pression n'a pas baissé, on lance l'arrosage
    } else{
        Serial.println("pressure drop detected ! switching state to read_sensors");//débogage
        state = read_sensors;//interrupteur éteint, qui simule que la pression a baissé, on repars sur la lecture des capteurs
      }
      Serial.println("_________");//débogage
      break; //on arrête l'éxecution du bout de programme


    case begin_water:
      //Le code pour le démarrage de l'eau n'est lui aussi pas terminé. Pour le moment, l'ouverture de la vanne est symbolisé par une led. 
      //On allume simplement la led pour symboliser que toutes les conditions sont réunies pour lancer un arrosage.
      digitalWrite(br_start_water, HIGH);//on allume la led, (arrosage a commencé)
      Serial.println("Turned on water");//débogage
      delay(10000); //timer de 30 min (10s pour les tests) à remplacer par millis pour vérification continue du niveau d'eau
      digitalWrite(br_start_water, LOW); //on éteint la led (couper l'arrosage) au bout des 30 min (10s pour tests)
      Serial.println("Turned off water");//débogage
      Serial.println("Case read_sensors successfully executed, switching state to read_sensors ");//débogage
      Serial.println("_________");//débogage
      state=read_sensors; //on repars sur l'état "read_sensors"
      break;//on arrête l'éxecution du bout de programme

    case low_water: //début de l'état low_water
      while (digitalRead(br_lvl_eau) == LOW) { //on vérifie que le niveau de l'eau soit toujours faible
        digitalWrite(br_led_wat_low, HIGH); //on allume la led, et le programme restera bloqué ici tant que l'utilisateur n'ajoute pas d'eau
      }
      //La suite s'éxecute si de l'eau est ajoutée
      Serial.println("Water level is good"); //sortie débogage
      Serial.println("Case low_water successfully executed switching state to read_sensors"); //sortie débogage
      Serial.println("_________"); //sortie débogage
      digitalWrite(br_led_wat_low, LOW); //on éteint la led niveau faible
      state = read_sensors; //on repars sur l'état "read_sensors"
      break; //on arrête l'éxecution du bout de programme
  }
}
