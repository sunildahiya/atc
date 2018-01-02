void serial_two(String str, double value){
  Serial.print(str);
  Serial.print("\t");
  Serial.print(value);
}

void serial_twoln(String str, double value){
  Serial.print(str);
  Serial.print("\t");
  Serial.println(value);
}

void serial_two(String str, int value){
  Serial.print(str);
  Serial.print("\t");
  Serial.print(value);
}

void serial_twoln(String str, int value){
  Serial.print(str);
  Serial.print("\t");
  Serial.println(value);
}

void serial_tab(double value){
  Serial.print(value);
  Serial.print("\t");
}


void serial_print(){
//  read_ultra();
//  find_moving_avg();
  serial_tab(stage);
  serial_tab(leftFrontDist);
  serial_tab(leftBackDist);
  serial_tab(movingAvgLeftFrontV);
  serial_tab(movingAvgLeftBackV);
  serial_tab(frontLeftDist);
  serial_tab(frontRightDist);
  serial_tab(movingAvgFrontLeftV);
  serial_tab(movingAvgFrontRightV);
  serial_tab(gyroZangle);
  serial_tab(angleError);
  serial_tab(xError);
  serial_tab(error);
  serial_tab(derror);
  Serial.println(correction);
  
//  Serial.print(stage);
//  Serial.print("\t");
//  Serial.print(leftFrontDist);
//  Serial.print("\t"); 
//  Serial.print(leftBackDist);
//  Serial.print("\t");
//  Serial.print(movingAvgLeftFrontV);
//  Serial.print("\t"); 
//  Serial.print(movingAvgLeftBackV);
//  Serial.print("\t");
//  Serial.print(frontLeftDist);
//  Serial.print("\t"); 
//  Serial.print(frontRightDist);
//  Serial.print("\t");
//  Serial.print(movingAvgFrontLeftV);
//  Serial.print("\t"); 
//  Serial.print(movingAvgFrontRightV);
//  Serial.print("t");
//  Serial.print("\t");
//  Serial.print(leftRefDist);
//  Serial.print("\t");
//  Serial.print(angleError);
//  Serial.print("\t");
//  Serial.print(xError);
//  Serial.print("\t");  
//  Serial.print(error);
//  Serial.print("\t");
//  Serial.print(derror);
//  Serial.print("\t");
//  Serial.println(correction);

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



//    Serial.print("sv_clean1FrontStop");
//    Serial.print("\t"); 
//    Serial.print("angleError");
//    Serial.print("\t"); 
//    Serial.print("leftBackDist");
//    Serial.print("\t");
//    Serial.println("sv_clean1LeftStopF");
//
//    
//    Serial.print(sv_clean1FrontStop);
//    Serial.print("\t"); 
//    Serial.print(angleError);
//    Serial.print("\t");
//    Serial.print(leftBackDist);
//    Serial.print("\t");
//    Serial.println(sv_clean1LeftStopF);
//    delay(60000);
//    stage = s_stop;
}



void serial_input_ctrl(){
  if (Serial.available()){
    int v = Serial.parseInt();
    if (v == 1){
       commodeRackMotor.anticlockwise(110);
        Serial.print("come");
    }
//      commodeRackMotor.anticlockwise(35);
    if (v == 2)
      commodeRackMotor.clockwise(110);
    if (v == 3)
      commodeRackMotor.stall();
//      stage = s_stop;
  } 
}

