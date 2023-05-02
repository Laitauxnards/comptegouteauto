    case begin_water:
      digitalWrite(br_start_water, HIGH);
      Serial.println("Turned on water");
      delay(10000); //timer de 30 min (10s pour les tests) à remplacer par millis pour vérification continue du niveau d'eau
      digitalWrite(br_start_water, LOW); //couper l'arrosage
      Serial.println("Turned off water");
      Serial.println("Case read_sensors successfully executed, switching state to read_sensors ");
      Serial.println("_________");
      state=read_sensors;
      break;