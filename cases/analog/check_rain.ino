    case check_rain:
      if (temps_save + 10800000 < millis()) { //décompte des 3h
        press_save = analogRead(br_press);
        Serial.println("3h timer ended ! Updating saved baro: "); //log
        Serial.print(press_save); //log
        Serial.println("updating saved time: "); //log
        Serial.print(temps_save); //log
   } if (analogRead(br_press)<(press_save - 5)) { //Baisse de 5 hpa constatée
        Serial.println("pressure drop detected ! switching state to begin_water");
        state = begin_water; //Switch vers la partie de code qui controle l'électrovanne
   }  else {
        Serial.println("no pressure drop detected ! switching state to read_sensors");
        state = read_sensors;
      }
      Serial.println("Case check_rain successfully executed using following settings: ");
      Serial.print("temps_save: ");
      Serial.println(analogRead(temps_save));
      Serial.print("press_save: ");        
      Serial.println(analogRead(press_save));
      Serial.print("br_press (live presure): ");
      Serial.println(analogRead(br_press));
      Serial.println("_________");
      break;
