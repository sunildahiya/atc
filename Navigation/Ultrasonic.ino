void init_ultra(){
  for (int i=0; i<5; i++)
    read_ultra();

  leftRefDist = 0;
  frontRefDist = 0;
  for (int i=0; i<50; i++){
    read_ultra();
    leftRefDist += (leftFrontDist+leftBackDist)/2; 
    frontRefDist += (frontLeftDist+frontRightDist)/2;
  }
  leftRefDist /= 50;
  frontRefDist /= 50;
  
  movingAvgLeftFrontV = 0;
  movingAvgLeftBackV = 0;
  movingAvgFrontLeftV = 0;
  movingAvgFrontRightV = 0;
  
  for (int i=0; i<10; i++){
    read_ultra();
    movingAvgLeftFrontV += leftFrontDist;
    movingAvgLeftBackV += leftBackDist;
    movingAvgLeftFront[i] = leftFrontDist;
    movingAvgLeftBack[i] = leftBackDist;

    movingAvgFrontLeftV += frontLeftDist;
    movingAvgFrontRightV += frontRightDist;
    movingAvgFrontLeft[i] = frontLeftDist;
    movingAvgFrontRight[i] = frontRightDist;
  }
  movingAvgLeftFrontV /= 10;
  movingAvgLeftBackV /= 10;
  movingAvgFrontLeftV /= 10;
  movingAvgFrontRightV /= 10;
  }

void read_ultra(){
  digitalWrite(leftFrontTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftFrontTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftFrontTrigPin, LOW);
  
  leftFrontDur = pulseIn(leftFrontEchoPin, HIGH);

  digitalWrite(leftBackTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftBackTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftBackTrigPin, LOW);
  leftBackDur = pulseIn(leftBackEchoPin, HIGH);
  
  digitalWrite(frontLeftTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontLeftTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontLeftTrigPin, LOW);
  frontLeftDur = pulseIn(frontLeftEchoPin, HIGH);

  digitalWrite(frontRightTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontRightTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontRightTrigPin, LOW);
  
  frontRightDur = pulseIn(frontRightEchoPin, HIGH);

  // Calculating the distance
  leftFrontDist= leftFrontDur*0.034/2-0.5;
  leftBackDist= leftBackDur*0.034/2+2;
  
  frontLeftDist= frontLeftDur*0.034/2+2;
  frontRightDist= frontRightDur*0.034/2;
  }

void find_moving_avg(){
  movingAvgLeftFrontV *= 10;
  movingAvgLeftBackV *= 10;
  movingAvgFrontLeftV *= 10;
  movingAvgFrontRightV *= 10;
  movingAvgLeftFrontV -= movingAvgLeftFront[0];
  movingAvgLeftBackV -= movingAvgLeftBack[0];
  movingAvgFrontLeftV -= movingAvgFrontLeft[0];
  movingAvgFrontRightV -= movingAvgFrontRight[0];
  
  for (int i=0; i<9; i++){
    movingAvgLeftFront[i] = movingAvgLeftFront[i+1];
    movingAvgLeftBack[i] = movingAvgLeftBack[i+1];
    movingAvgFrontLeft[i] = movingAvgFrontLeft[i+1];
    movingAvgFrontRight[i] = movingAvgFrontRight[i+1];
  }

  movingAvgLeftFront[9] =  leftFrontDist;
  movingAvgLeftBack[9] = leftBackDist;
  movingAvgLeftFrontV += movingAvgLeftFront[9];
  movingAvgLeftBackV += movingAvgLeftBack[9];
  movingAvgLeftFrontV /= 10;
  movingAvgLeftBackV /= 10;

  movingAvgFrontLeft[9] =  frontLeftDist;
  movingAvgFrontRight[9] = frontRightDist;
  movingAvgFrontLeftV += movingAvgFrontLeft[9];
  movingAvgFrontRightV += movingAvgFrontRight[9];
  movingAvgFrontLeftV /= 10;
  movingAvgFrontRightV /= 10;
}


