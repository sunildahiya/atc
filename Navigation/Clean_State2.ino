void clean_state2(){
  if(stage == s_clean2F){
    serial_twoln("Chutiya:\t", stage);
    if (frontLeftDist > sc_clean2FStopDist){
      read_ultra();
      find_moving_avg();
      correction = 0;
      apply_correction(forward);  
    }
    else{
      apply_correction(0);
      stage = s_clean2R;
      delay(1000);
    }
  }

  else if(stage == s_clean2R){
    serial_twoln("Chutiya:\t", stage);
    rotate_imu(c_clockwise, 90);
    delay(200);
    recalibrate();
//    allign(front, 0);
    delay(500);
    recalibrate();
    stage = s_clean2P;
  }

  else if(stage == s_clean2P){
    serial_twoln("Chutiya:\t", stage);
    if (frontLeftDist > sc_clean2PStopDist){
      read_ultra();
      find_moving_avg();
//      calc_correction(forward, front, -1);
      correction = 0;
      apply_correction(forward); 
    }
    else{
      apply_correction(0);
      stage = s_clean223; 
      delay(1000);
    }
  }

  else if(stage == s_clean223){
    serial_twoln("Chutiya:\t", stage);
    recalibrate();
    calc_correction(forward, left, -1);
    rotate_imu(c_anticlockwise, 90);
    delay(300);
    recalibrate();
//    allign(front, 0);
    delay(200);
    recalibrate();
    stage = s_clean3F;
  }

  else if(stage == s_clean3F){
    serial_twoln("Chutiya:\t", stage);
    if (frontLeftDist > sc_clean3FStopDist){
      read_ultra();
      find_moving_avg();
      correction = 0;
      apply_correction(forward);
    }
    else{
      stage = s_clean3R;
      apply_correction(0);
    }
  }

  else if(stage == s_clean3R){
    serial_twoln("Chutiya:\t", stage);
//    recalibrate();
//    calc_correction(forward, front, -1);
    rotate_imu(c_anticlockwise, 90);
    delay(200);
    recalibrate();    
    stage = s_clean3P;
  }

  else if(stage == s_clean3P){
    serial_twoln("Chutiya:\t", stage);
    if (frontRightDist > sc_clean3PStopDist){
      read_ultra();
      find_moving_avg();
      correction = 0;
      apply_correction(forward);
    }
    else{
      apply_correction(0);
      stage = s_clean32C;
      delay(1000);
    } 
  }

  else if(stage == s_clean32C){
    serial_twoln("Chutiya:\t", stage);
    recalibrate();
    rotate_imu(c_anticlockwise, 90);
    delay(500);
    allign(left, 0);
    delay(500);
    stage = s_cleanCB;
    recalibrate();
    
  }

  else if(stage == s_cleanCB){
    serial_twoln("Chutiya:\t", stage);
    correction = 0;
    while(digitalRead(commodeIRPin) == 1)
      apply_correction(backward);
    apply_correction(0);
    delay(1000);
    stage = s_cleanCommode;
    recalibrate();
  }
  else if(stage == s_cleanCommode){
    Serial.println("Start");
    commodeServo.write(final_angle);
    for (int i=0; i<3; i++){
      commodeCleanMotor.anticlockwise(130);
      move_rack(down, 200);
      move_rack(down);
      move_rack(up, 200);
      move_rack(up);
    }
    commodeServo.write(initial_angle);
    commodeCleanMotor.stall();
    stage = s_cleanCF;
    commodeServo.write(0); 
    Serial.println("Finish");
  }

  else if (stage == s_cleanCF){
    if (frontRightDist > sc_cleanCFStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, left, leftRefDist);
      apply_correction(forward);
    }
    else{
      apply_correction(0);
      delay(1000);
      stage = s_cleanC23;
    }
  }

  if (stage == s_cleanC23){
    recalibrate();
    allign(front, 0);
    delay(1000);
    calc_correction(forward, front, -1);
    rotate_imu(c_clockwise, 90);
    delay(1000);
    stage = s_clean3P2;
    recalibrate();
  }

  if (stage == s_clean3P2){
    if (frontRightDist > marginDist){
      read_ultra();
      correction = 0;
      apply_correction(forward);
    }
    else{
      apply_correction(0);
      stage = s_clean324;
      delay(1000);
    }
  }

  if (stage == s_clean324){
    rotate_imu(c_clockwise, 90);
    delay(400);
    recalibrate();
    allign(front, 0);
    delay(1000);
    stage = s_clean4F;
    recalibrate();
  }

  else if (stage == s_clean4F){
    if (frontRightDist > marginDist){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, front, -1);
      apply_correction(forward);
    }
    else{
      apply_correction(0);
      delay(1000);
      stage = s_clean4RSlight;
    }
  }

  else if(stage == s_clean4RSlight){
    rotate_imu(c_anticlockwise, sc_clean4RSlight);
    delay(1000);
    stage = s_clean4B;
  }

  else if(stage == s_clean4B){
    if (frontRightDist < sc_clean4BStopDist){
      read_ultra();
      correction = 0;
      apply_correction(backward);
    }
    else{
      apply_correction(0);
      stage = s_clean425;
      delay(1000);
    }
  }

  else if(stage == s_clean425){
    recalibrate();
    rotate_imu(c_clockwise, 90+sc_clean4RSlight);
    delay(1000);
    allign(front, 0);
    delay(1000);
    stage = s_clean5F;
    recalibrate();
  }

  else if(stage == s_clean5F){
    if (frontRightDist > sc_clean5FStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, front, -1);
      apply_correction(forward);
    }
    else{
      apply_correction(0);
      stage = s_clean5R;
      delay(1000);
    }
  }

  else if(stage == s_clean5R){
    rotate_imu(c_anticlockwise, 90);
    delay(1000);
    recalibrate();
    allign(front, 0);
    delay(1000);
    stage = s_clean5P;
    recalibrate();
  }

  else if(stage == s_clean5P){
    if (frontRightDist > marginDist){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, front, -1);
      apply_correction(forward);
    }
    else{
      apply_correction(0);
      delay(1000);
      stage = s_clean5B;
      recalibrate();
    }
  }

  else if(stage == s_clean5B){
    if (frontRightDist < sc_clean5BStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(backward, front, -1);
      apply_correction(backward);
    }
    else{
      apply_correction(0);
      stage = s_cleanRetR;
      delay(1000);
      state = 3;
    }
  }
}


