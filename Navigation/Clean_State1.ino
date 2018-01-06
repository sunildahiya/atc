void clean_state1_ent1(){
    Serial.println("Entry");
    if(stage == s_clean1LeftSAllign){
      serial_twoln("Chutiya:\t", stage);
      allign(left, 0.0);
      delay(100);
      read_ultra();
      find_moving_avg();
      leftRefDist = movingAvgLeftBackV;
      stage = s_clean1LeftS;
    }
    else if(stage == s_clean1LeftS){
      serial_twoln("Chutiya:\t", stage);
      if (frontRightDist > sc_clean1LeftSStopDist){
        read_ultra();
        find_moving_avg();
        calc_correction(forward, left, leftRefDist);
        apply_correction(forward);
      }
      else
        stage = s_clean1FrontS;
    }
    else if(stage == s_clean1FrontS){
      serial_twoln("Chutiya:\t", stage);
      if (frontRightDist > marginDist){
        read_ultra();
        find_moving_avg();
        calc_correction(forward, front, -1);
        apply_correction(forward);
        serial_print();
      }
      else{
        apply_correction(0);
        stage = s_clean1FrontSB;
        delay(1000);
        recalibrate();
      }
    }
    else if(stage == s_clean1FrontSB){
      serial_twoln("Chutiya:\t", stage);
      if (frontRightDist < sc_clean1FrontSBStopDist){
        read_ultra();
        find_moving_avg();
        calc_correction(backward, front, -1);
        apply_correction(backward);
      }
      else{
        stage = s_clean1LeftSB;
        recalibrate();
      }
    }
    else if(stage == s_clean1LeftSB){
      serial_twoln("Chutiya:\t", stage);
      if (frontLeftDist < sc_clean1LeftSBStopDist){
        read_ultra();
        find_moving_avg();
        calc_correction(backward, left, leftRefDist);
        apply_correction(backward);
      }
      else{
        apply_correction(0);
        delay(500);
        allign(left, 0);
        delay(1000);
        sv_clean1FrontStop = frontRightDist-87.63+frontLeftOmniDist;
        stage = s_clean1LeftSRotSlight;
      }
    }
    else if(stage == s_clean1LeftSRotSlight){
      serial_twoln("Chutiya:\t", stage);
      allign(left, sc_clean1LeftSRotAngle);
//      rotate_imu(c_clockwise, sc_clean1LeftSRotAngle);
      stage = s_clean1LeftSTilt;
      delay(1000);
      calc_correction(forward, left, -1);
      sv_clean1LeftStopF = leftBackOmniDist*(1-tan(angleError*3.14/180))+sv_clean1FrontStop*tan(angleError*3.14/180)/cos(angleError*3.14/180)+leftBackDist-29;

    }
    else if(stage == s_clean1LeftSTilt){
      serial_twoln("Chutiya:\t", stage);
      if (leftBackDist < sv_clean1LeftStopF){
        read_ultra();
        find_moving_avg();
        correction = 0;
        apply_correction(forward);
      }
      else{
        apply_correction(0);
        stage = s_clean1LeftSAllign2;
        delay(1000);  
      }
    }

    else if(stage == s_clean1LeftSAllign2){
      serial_twoln("Chutiya:\t", stage);
      read_ultra();
      find_moving_avg();
      rotate_imu(c_anticlockwise, angleError);
      allign(left, 0.0);
      recalibrate();
      stage = s_clean1F;
    }

    else if(stage == s_clean1F){
      serial_twoln("Chutiya:\t", stage);
      if (frontRightDist > sc_clean1FStopDist){
        read_ultra();
        find_moving_avg();
        calc_correction(forward, front, -1);
        apply_correction(forward);
      }
      else{
        stage = s_clean122;
        apply_correction(0);
        delay(1000);
      }
    }

    else if(stage == s_clean122){
      serial_twoln("Chutiya:\t", stage);
      serial_print();
      rotate_imu(c_clockwise, 90);
      delay(600);
      recalibrate();
      allign(left, 0);
      long initial_ = millis();
      long timePassed = 0;
      while (timePassed < 600){
        correction = 0;
        apply_correction(forward);
        timePassed = millis()-initial_;
      }
      stage = s_clean2F;
      state = 2;
    }
}


void clean_state1_ent2(){
    state = 2;
    stage = s_clean2F;
    finishStarting = true;
}

void clean_state1_ent3(){
  Serial.println(stage);
  if (stage == s3_clean1F){
      if (frontRightDist > sc3_clean1FStopDist){
        read_ultra();
        find_moving_avg();
        calc_correction(forward, front, -1);
        apply_correction(forward);
      }
      else{
        apply_correction(0);
        delay(500);
        stage = s3_clean122;
      }
  }
  else if(stage == s3_clean122){
    rotate_imu(c_clockwise, 90);
    delay(500);
    stage = s3_clean2FLS;
    recalibrate();
    leftRefDist = movingAvgLeftBackV;
  }
  else if(stage == s3_clean2FLS){
    if (frontRightDist > sc3_clean2FLSStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, left, leftRefDist);
      apply_correction(forward);
    }
    else
      stage = s3_clean2FFS;
  }
  else if(stage == s3_clean2FFS){
    if (frontRightDist > marginDist+15){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, front, -1);
      apply_correction(forward);
    }
    else{
      apply_correction(0);
      delay(500);
      stage = s3_clean223;
    }
  }
  else if(stage == s3_clean223){
    rotate_imu(c_clockwise, 90);
    delay(500);
    stage = s_clean1LeftSAllign;
    state = 1;
    finishStarting = true;
    Serial.println("Exit");
  }
}

