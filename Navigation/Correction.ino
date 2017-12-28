void calc_correction(int dir, int sensor, int shiftRef, double angleRef = 0){
  if (sensor == front)
    angleError = (movingAvgFrontRightV-movingAvgFrontLeftV)*180/(frontUltraDist*3.14);
  else if (sensor == left)
    angleError = (movingAvgLeftFrontV-movingAvgLeftBackV)*180/(leftUltraDist*3.14);

  angleError -= angleRef;
  if (shiftRef != -1)
    xError = (movingAvgLeftFrontV+movingAvgLeftBackV)/2 - shiftRef;
  else
    xError = 0;
    
  if (dir == 1)
    error = 0.6*xError + 0.7*angleError;
  else if(dir == -1)
    error = 0.8*xError - 1.4*angleError;
  derror = error-prevError;
  prevError = error;
  correction = kp*error + kd*derror;
  correction = limit(correction, -45, 45);
//  correction = fuzzy.centroid_correction(error, derror);
//  correction = 0;
}

int limit(int value, int lowestValue, int highestValue){
  if (value < lowestValue)
    value = lowestValue;
  else if (value > highestValue)
    value = highestValue;
  return value;
}

void rotate_dur(int dir, int duration){
  long start = millis();
  int timePassed = 0;
  if (dir == c_clockwise){
    while(timePassed < duration){
      motorRight.anticlockwise(basePWMRotate_d-20);
      motorLeft.clockwise(basePWMRotate_d);
      timePassed = millis()-start;
    }
  }
  else if(dir == c_anticlockwise){
    while(timePassed < duration){
      motorRight.clockwise(basePWMRotate_d-20);
      motorLeft.anticlockwise(basePWMRotate_d);
      timePassed = millis()-start;
    }
  }
  apply_correction(0);
  stop_b = 1;
}

void rotate(int dir, int correction){
  if (dir == c_clockwise){
      motorRight.anticlockwise(basePWMRotate_s-correction);
      motorLeft.clockwise(basePWMRotate_s-correction);
  }
  else if(dir == c_anticlockwise){
      motorRight.clockwise(basePWMRotate_s-correction);
      motorLeft.anticlockwise(basePWMRotate_s-correction);
  }
}

void allign(int sensor, double angleRef = 0.0){
  read_ultra();
  find_moving_avg();
  if (sensor == front)
    angleError = (movingAvgFrontRightV-movingAvgFrontLeftV)*180/(frontUltraDist*3.14);
  else if (sensor == left)
    angleError = (movingAvgLeftFrontV-movingAvgLeftBackV)*180/(leftUltraDist*3.14);

//  angleError = angleRef-angleError;
  angleError -= angleRef;
  double allignKp = 1.6, allignKd = 0.2;
  double allignDerror = 0;
  double allignPrevError = angleError;
  double allignCorrection = 0;
  
//  serial_print();
  while (angleError < -1 || angleError > 1){
    allignCorrection = allignKp*angleError + allignKd*allignDerror;
    
    if (angleError > 0)
      rotate(c_anticlockwise, abs(allignCorrection));
    else
      rotate(c_clockwise, abs(allignCorrection));
    read_ultra();
    find_moving_avg();
    if (sensor == front)
      angleError = (movingAvgFrontRightV-movingAvgFrontLeftV)*180/(frontUltraDist*3.14);
    else if (sensor == left)
      angleError = (movingAvgLeftFrontV-movingAvgLeftBackV)*180/(leftUltraDist*3.14);
//    angleError = angleRef-angleError;
    angleError -= angleRef;
    allignDerror = angleError - allignPrevError;
    allignPrevError = angleError;
    
//    serial_print();
  }
//  Serial.println("Out");
//  Serial.print("Allign anglerror");
//  Serial.println(angleError);
  apply_correction(0);
}

void apply_correction(int dir){
  if (dir == forward){
    motorRight.clockwise(basePWM-correction);
    motorLeft.clockwise(basePWM+correction-28);
  }
  else if (dir == backward){
    motorRight.anticlockwise(basePWM-correction);
    motorLeft.anticlockwise(basePWM+correction-28);
  }
  else{
    motorRight.stall();
    motorLeft.stall();
  } 
}


//void apply_correction(int dir){
//  angleError = angle*180;
//  xError = x;
//  error = 0.7*xError + 0.3*angleError;
//  derror = error-prevError;
//  prevError = error;
//  correction = kp*error + kd*derror;
//  correction = limit(correction, -40, 40);
////  correction = fuzzy.centroid_correction(error, derror);
////  correction = 0;
//  
//}



