  switch(state){
    case read_sensors:
      digitalWrite(br_start_water, LOW); //couper l'arrosage
      night = digitalRead(br_nuit); //a remplacer par un script photo résistance
      if (digitalRead(br_lvl_eau) == LOW) { //s'assurer que le niveau d'eau est correct 
        Serial.println("Low water ! Switching state to low_water");
        state = low_water;
        break;
      }
      if (analogRead(br_nuit)<380) {
        Serial.println("Night is true");
        if (map(analogRead(0), 520, 250, 0, 100)<set_moist) { //vérifier que la terre est moins humide que défini par l'utilisateur
          Serial.println("Soil is dry ! Switching state to check_rain");
          state = check_rain;
        } 
      } else {
          Serial.println("Nothing detected, Switching state to read_sensors");
          state=read_sensors;
        }
      Serial.println("Case read_sensors successfully executed using following settings: ");
      Serial.print("br_nuit: ");
      Serial.println(analogRead(br_nuit));
      Serial.print("br_lvl_eau: ");        
      Serial.println(digitalRead(br_lvl_eau));
      Serial.print("br_soil_moist: ");
      Serial.print(map(analogRead(0), 520, 250, 0, 100));
      Serial.println("%");
      Serial.print("br_soil_moist: ");
      Serial.println(analogRead(br_soil_moist));
      Serial.println("_________");
      delay(1000);
