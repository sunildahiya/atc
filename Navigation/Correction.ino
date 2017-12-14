int limit(int value, int lowestValue, int highestValue){
  if (value < lowestValue)
    value = lowestValue;
  else if (value > highestValue)
    value = highestValue;
  return value;
}


void apply_correction(int dir){
  angleError = angle*180;
  xError = x;
  error = 0.7*xError + 0.3*angleError;
  derror = error-prevError;
  prevError = error;
  correction = kp*error + kd*derror;
  correction = limit(correction, -30, 30);
//  correction = fuzzy.centroid_correction(error, derror);
  
  if (dir == forward){
    motorRight.clockwise(basePWM-correction);
    motorLeft.clockwise(basePWM+correction);
  }
  else if (dir == backward){
    motorRight.anticlockwise(basePWM-correction);
    motorLeft.anticlockwise(basePWM+correction);
  }
  else{
    motorRight.stall();
    motorLeft.stall();
  }
  
}

