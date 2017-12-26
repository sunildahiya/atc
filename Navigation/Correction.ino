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
      motorRight.anticlockwise(baseRotatePWM);
      motorLeft.clockwise(baseRotatePWM-28);
      timePassed = millis()-start;
    }
  }
  else if(dir == c_anticlockwise){
    while(timePassed < duration){
      motorRight.clockwise(baseRotatePWM);
      motorLeft.anticlockwise(baseRotatePWM-28);
      timePassed = millis()-start;
    }
  }
  apply_correction(0);
  stop_b = 1;
}

void rotate(int dir){
  if (dir == c_clockwise){
      motorRight.anticlockwise(170);
      motorLeft.clockwise(170);
  }
  else if(dir == c_anticlockwise){
      motorRight.clockwise(170);
      motorLeft.anticlockwise(170);
  }
}

void allign(int sensor){
  read_ultra();
  find_moving_avg();
  if (sensor == front)
    angleError = (movingAvgFrontRightV-movingAvgFrontLeftV)*180/(frontUltraDist*3.14);
  else if (sensor == left)
    angleError = (movingAvgLeftFrontV-movingAvgLeftBackV)*180/(leftUltraDist*3.14);

  Serial.print("Angle error:\t");
  Serial.println(angleError);
  double kp = 2, kd = 0.2;
  while (angleError < -1 || angleError > 1){
    if (angleError > 0)
      rotate(c_anticlockwise);
    else
      rotate(c_clockwise);
    if (sensor == front)
      angleError = (movingAvgFrontRightV-movingAvgFrontLeftV)*180/(frontUltraDist*3.14);
    else if (sensor == left)
      angleError = (movingAvgLeftFrontV-movingAvgLeftBackV)*180/(leftUltraDist*3.14);
    read_ultra();
    find_moving_avg();
    Serial.print("Angle error:\t");
    Serial.println(angleError);
  }
  Serial.print("Angle error:\t");
  Serial.println(angleError);
  apply_correction(0);
}

void apply_correction(int dir){
  if (dir == forward){
    motorRight.clockwise(basePWM-correction);
    motorLeft.clockwise(basePWM+correction-28);
  }
  else if (dir == backward){
    motorRight.anticlockwise(basePWM-correction);
    motorLeft.anticlockwise(basePWM+correction-40);
  }
  else{
    motorRight.stall();
    motorLeft.stall();
  }
}

void calc_correction(int dir, int sensor, double reference){
  if (sensor == front)
    angleError = (movingAvgFrontRightV-movingAvgFrontLeftV)*180/(frontUltraDist*3.14);
  else if (sensor == left)
    angleError = (movingAvgLeftFrontV-movingAvgLeftBackV)*180/(leftUltraDist*3.14);
  xError = (movingAvgLeftFrontV+movingAvgLeftBackV)/2 - reference;
//  xError = 0;
  if (dir == 1)
    error = 0.6*xError + 0.7*angleError;
  else if(dir == -1)
    error = 0.6*xError - 0.7*angleError;
  derror = error-prevError;
  prevError = error;
  correction = kp*error + kd*derror;
  correction = limit(correction, -45, 45);
//  correction = fuzzy.centroid_correction(error, derror);
//  correction = 0;
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



