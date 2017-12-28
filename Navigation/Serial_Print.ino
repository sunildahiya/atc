void serial_print(){
//  read_ultra();
//  find_moving_avg();
  Serial.print(stage);
  Serial.print("\t");
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
  Serial.print(movingAvgFrontRightV);
//  Serial.print("\t");
//  Serial.print(leftRefDist);
  Serial.print("\t");
  Serial.print(angleError);
  Serial.print("\t");
  Serial.print(xError);
  Serial.print("\t");  
  Serial.print(error);
  Serial.print("\t");
  Serial.print(derror);
  Serial.print("\t");
  Serial.println(correction);

//  Serial.print(frontLeftDist);
//  Serial.print("\t"); 
//  Serial.print(frontRightDist);
//  Serial.print("\t");
//  Serial.print(movingAvgFrontLeftV);
//  Serial.print("\t"); 
//  Serial.println(movingAvgFrontRightV);

  
//  Serial.print(encoderValueLeft);
//  Serial.print("\t"); 
//  Serial.print(encoderValueRight);
//  Serial.print("\t");
//  Serial.print(x);
//  Serial.print("\t");
//  Serial.print(y);
//  Serial.print("\t");
//  Serial.print(angle);
//  Serial.print("\t");  
//  Serial.print(error);
//  Serial.print("\t");
//  Serial.print(derror);
//  Serial.print("\t");
//  Serial.println(correction);
}

