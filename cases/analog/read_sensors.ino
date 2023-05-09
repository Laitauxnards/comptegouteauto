  switch(state){
    case read_sensors:
      digitalWrite(br_start_water, LOW); //couper l'arrosage
      night = analogRead(br_nuit); //a remplacer par un script photo résistance (avec quantum comme potentiomètre)
      if (analogRead(br_lvl_eau) == LOW) { //s'assurer que le niveau d'eau est correct 
        Serial.println("Low water ! Switching state to low_water");
        state = low_water;
        break;
      }
      if (analogRead(br_nuit)==LOW) {
        Serial.println("Night is true");
        if map(analogRead(0), 500, 250, 0, 100)<set_moist { //vérifier que la terre est moins humide que défini par l'utilisateur
          Serial.println("Soil is dry ! Switching state to check_rain");
          state = check_rain;
        } 
      } else {
          Serial.println("Nothing detected, Switching state to read_sensors");
          state=read_sensors;
        }
      Serial.println("Case read_sensors successfully executed using following settings: ");
      Serial.print("br_nuit: ");
      Serial.println(anallogRead(br_nuit));
      Serial.print("br_lvl_eau: ");        
      Serial.println(analogRead(br_lvl_eau));
      Serial.print("br_soil_moist: ");
      Serial.println(analogRead(br_soil_moist));
      Serial.println("_________");
      delay(1000);
      break;
