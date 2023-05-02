    case begin_water:
      digitalWrite(br_start_water, HIGH);
      Serial.println("Turned on water");
      delay(1800000); //timer de 30 min à remplacer par millis pour vérification continue du niveau d'eau
      Serial.println("Case read_sensors successfully executed, switching state to read_sensors ");
      state=read_sensors;
      break;