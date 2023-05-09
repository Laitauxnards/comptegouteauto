    case low_water:
      while (digitalRead(br_lvl_eau) == HIGH) {
        digitalWrite(br_led_wat_low, HIGH);
      }
      Serial.println("Water level is good");  
      Serial.println("Case low_water successfully executed switching state to read_sensors");
      Serial.println("_________");  
      digitalWrite(br_led_wat_low, LOW);  
      state = read_sensors;
      break;//test
