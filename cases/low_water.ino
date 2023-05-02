    case low_water:
      while (digitalRead(br_start_water) == HIGH) {
        digitalWrite(br_led_wat_low, HIGH);
      serial.println("Water level is good");  
      Serial.println("Case low_water successfully executed switching state to read_sensors");
   }  state = read_sensors;
      break;