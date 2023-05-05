  switch(state){
    case read_sensors:
      digitalWrite(br_start_water, LOW); //couper l'arrosage
      night = digitalRead(br_nuit); //a remplacer par un script photo résistance (avec quantum comme potentiomètre)
      if (digitalRead(br_lvl_eau) == LOW) { //s'assurer que le niveau d'eau est correct 
        Serial.println("Low water ! Switching state to low_water");
        state = low_water;
        break;
      }
      if (digitalRead(br_nuit)==LOW) {
        Serial.println("Night is true");
        // if (digitalRead(br_soil_moist) < set_moist) { //vérifier que la terre est moins humide que défini par l'utilisateur
        if (digitalRead(br_soil_moist) == LOW) {
          Serial.println("Soil is dry ! Switching state to check_rain");
          state = check_rain;
        } 
      } else {
          Serial.println("Nothing detected, Switching state to read_sensors");
          state=read_sensors;
        }
      Serial.println("Case read_sensors successfully executed using following settings: ");
      Serial.print("br_nuit: ");
      Serial.println(digitalRead(br_nuit));
      Serial.print("br_lvl_eau: ");        
      Serial.println(digitalRead(br_lvl_eau));
      Serial.print("br_soil_moist: ");
      Serial.println(digitalRead(br_soil_moist));
      Serial.println("_________");
      delay(1000);
      break;