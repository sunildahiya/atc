void clean_state3_ent12(){
    if(stage == s_cleanRetR){
      rotate_imu(c_anticlockwise, 180);
      delay(1000);
      recalibrate();
      allign(left, 0);
      delay(1000);
      stage = s_cleanRetF;
      recalibrate();
      leftRefDist = leftBackDist;
    }

    else if(stage == s_cleanRetF){
      if (frontRightDist > sc_cleanRetFStopDist){
        read_ultra();
        find_moving_avg();
        calc_correction(forward, left, leftRefDist);
        apply_correction(forward);
      }
      else{
        apply_correction(0);
        stage = s_cleanRetFinish;
        delay(1000);
      }
    }

    else if(stage == s_cleanRetFinish){
      rotate_imu(c_clockwise, 90);
      delay(1000);
      recalibrate();
      allign(left, 0);
      delay(1000);
      if (entranceNo == 2)
        stage = s_clean1LeftS;
      recalibrate();
    }
    
//   <------------------------------------------- entranceNo 2 ------------------------------------------> 
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
        stage = s2_cleanlR;
        delay(1000);
        recalibrate();
      }
    }
    else if(state == s2_cleanlR){
      rotate_imu(c_clockwise, 90);
      stage = s_stop;
      state = 4;
    }
}

void clean_state3_ent3(){
  if (stage == s_cleanRetR){
    rotate_imu(c_clockwise, 90);
    delay(500);
    stage = s3_cleanRetF;
  }

  else if(stage == s3_cleanRetF){
    if (frontRightDist < sc3_cleanRetFStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(backward, front, -1);
      apply_correction(backward);
    }
    else{
      apply_correction(0);
      stage = s_stop;
      state = 4;
    }
  }
}
