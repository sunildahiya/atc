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
      rotate(c_clockwise, 0);
      Serial.print("Start:\t");
      Serial.println(start_i);
    }
   } 
}

void rotate_util(){
  if (Serial.available()){
    int c = Serial.parseInt();
   if (c == 1){
      Serial.println("Duration");
      rotate_dur(c_clockwise, rotDur);
      Serial.println("Allign");
      allign(front);
      read_ultra();
      find_moving_avg();
      Serial.println("<-------------End---------------->");
      Serial.print(leftFrontDist);
      Serial.print("\t"); 
      Serial.print(leftBackDist);
      Serial.print("\t");
      Serial.print(movingAvgLeftFrontV);
      Serial.print("\t"); 
      Serial.print(movingAvgLeftBackV);
      Serial.print("\t");
      Serial.print(frontLeftDist);
      Serial.print("\t"); 
      Serial.print(frontRightDist);
      Serial.print("\t");
      Serial.print(movingAvgFrontLeftV);
      Serial.print("\t"); 
      Serial.println(movingAvgFrontRightV);
    }
  }
}

