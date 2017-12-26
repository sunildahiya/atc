int limit(int value, int lowestValue, int highestValue){
  if (value < lowestValue)
    value = lowestValue;
  else if (value > highestValue)
    value = highestValue;
  return value;
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



