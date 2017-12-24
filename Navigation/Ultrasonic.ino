void read_ultra(){
  // Clears the trigPin
  digitalWrite(rightFrontTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightFrontTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightFrontTrigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  rightFrontDur = pulseIn(rightFrontEchoPin, HIGH);
  
  digitalWrite(rightBackTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightBackTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightBackTrigPin, LOW);
  rightBackDur = pulseIn(rightBackEchoPin, HIGH);

  // Calculating the distance
  rightFrontDist= rightFrontDur*0.034/2+1;
  rightBackDist= rightBackDur*0.034/2;
  }

void find_moving_avg(){
  movingAvgRightFrontV *= 10;
  movingAvgRightBackV *= 10;
  movingAvgRightFrontV -= movingAvgRightFront[0];
  movingAvgRightBackV -= movingAvgRightBack[0];
  
  for (int i=0; i<9; i++){
    movingAvgRightFront[i] = movingAvgRightFront[i+1];
    movingAvgRightBack[i] = movingAvgRightBack[i+1];
  }

  movingAvgRightFront[9] =  rightFrontDist;
  movingAvgRightBack[9] = rightBackDist;
  movingAvgRightFrontV += movingAvgRightFront[9];
  movingAvgRightBackV += movingAvgRightBack[9];
  movingAvgRightFrontV /= 10;
  movingAvgRightBackV /= 10;
}

