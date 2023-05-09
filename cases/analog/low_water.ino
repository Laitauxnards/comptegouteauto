    case low_water:
      while (analogRead(br_lvl_eau) == HIGH) {
        analogWrite(br_led_wat_low, HIGH);
      }
      Serial.println("Water level is good");  
      Serial.println("Case low_water successfully executed switching state to read_sensors");
      Serial.println("_________");  
      analogWrite(br_led_wat_low, LOW);  
      state = read_sensors;
      break;
