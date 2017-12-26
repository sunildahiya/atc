void time_count(){
  if (Serial.available()){
    int c = Serial.parseInt();
    if (c == 1){
      apply_correction(0);
      Serial.print("TimePassed:\t");
      long timePassed = millis()-start_i;
      Serial.println(timePassed);
    }
    else if(c == 2){
      start_i = millis();
      rotate(c_clockwise);
      Serial.print("Start:\t");
      Serial.println(start_i);
    }
   } 
}
