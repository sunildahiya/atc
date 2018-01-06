void test_motor(){
  commodeCleanMotor.clockwise(55);
  mopMotor.anticlockwise(55);
  rollerMotor.clockwise(55);
  motorRight.clockwise(55);
  motorLeft.clockwise(55);
}
void test_rack_motor(){
  while(1)
    serial_input_ctrl();
}

void test_rack_IR(){
  commodeCleanMotor.anticlockwise(130);
  move_rack(down, 200);
  move_rack(down);
  move_rack(up, 200);
  move_rack(up);
  commodeCleanMotor.stall();
}

void test_ultra(){
  while(1){
    read_ultra();
    find_moving_avg();
    serial_print();
  }
}

void test_imu(){
  while(1){
    read_imu();
    serial_twoln("GyroAngle:\t", gyroZangle);
  }
}
//void read_android(){
////  Serial2.flush();
//  while (1){
////  Serial2.flush();
//    if (Serial2.available()){
//      char c = Serial2.read();  
//      if (c != START_CMD_CHAR)
//        break;
//      else{
//        temp = Serial2.parseFloat();
//        temp = Serial2.parseFloat();
//        temp = Serial2.parseInt();
//        androidAngle = temp;
//        temp = Serial2.parseFloat();
//      }
//    }
//  }
//}

