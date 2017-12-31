#include <Servo.h>
#include <Driver.h>
#include <Fuzzy.h>
#include <Wire.h>

//Constants
#define wheelSeparation 39
#define wheelRadius 5
#define leftUltraDist 33  
#define frontUltraDist 25.5  
#define leftBackOmniDist 40
#define frontLeftOmniDist 18.5
#define forward 1
#define backward -1
#define front 1
#define left -1
#define c_clockwise 1
#define c_anticlockwise -1
#define rotDur 2400
#define entryDist 130 
#define marginDist 30
#define sc_clean1FrontSStopDist 50
#define sc_clean1LeftSStopDist 105 
#define sc_clean1LeftSRotAngle 16
#define sc_clean1LeftSTiltDist 16

#define s_entry 1
#define s_clean1LeftSAllign 2
#define s_clean1LeftS 3
#define s_clean1FrontS 4
#define s_clean1FrontSB 5
#define s_clean1LeftSB 6
#define s_clean1LeftSRotSlight 7
#define s_clean1FrontRightSShift 9 
#define s_clean1LeftSRot90 10
#define s_stop -1
#define s_clean1LeftSTilt 12
#define s_clean12clean2 13


#define s_clean1LeftSAllign2 14
#define s_clean1F 15
#define s_clean122 16

#define s_clean2F 17
//#define s_clean2B 15
#define s_clean2R 18
#define s_clean2P 19
#define s_clean223R 20
#define s_clean223F 21
#define s_clean223R2 22
#define s_clean3F 23
#define s_clean32CR 25

double leftRefDist = 20;
double frontRefDist = 25;
double sv_clean1LeftStopF = 0, sv_clean1LeftStopI = 0, sv_clean1FrontStop = 0;

//Encoder Interrupt Pins
#define encoderPinRight1 18
#define encoderPinRight2 19
#define encoderPinLeft1 20
#define encoderPinLeft2 21

//Motor Driver Pins
#define motorRightEnPin 8
#define motorRightDirPin1 39
#define motorRightDirPin2 37
#define motorLeftEnPin 4
#define motorLeftDirPin1 23
#define motorLeftDirPin2 22

//Ultrasonic Sensors Left
#define leftFrontTrigPin A6 
#define leftFrontEchoPin A7  
#define leftBackTrigPin A3
#define leftBackEchoPin  A2 

//Ultrasonic Sensors Front
#define frontLeftTrigPin A8
#define frontLeftEchoPin A9  
#define frontRightTrigPin A5 
#define frontRightEchoPin A4 
 
//Motor Driver Objects
Driver motorRight(motorRightDirPin1, motorRightDirPin2, motorRightEnPin);
Driver motorLeft(motorLeftDirPin1, motorLeftDirPin2, motorLeftEnPin);

//Fuzzy
//Fuzzy fuzzy(12, 5, 40, 0); //error, derror, correction and centre

double kp = 10, kd = 0;
double error = 0, derror = 0, prevError = 0, correction = 0;
double xError = 0, angleError = 0;
int basePWM = 100;
int basePWMRotate_d = 100;
int basePWMRotate_s = 130;
volatile int lastEncodedRight = 0;
volatile long encoderValueRight = 0;
long prevEncoderValueRight = 0;

volatile int lastEncodedLeft = 0;
volatile long encoderValueLeft = 0;
long prevEncoderValueLeft = 0;

double x = 0, y = 0, angle = 0;

long leftFrontDur = 0, leftBackDur = 0;
double leftFrontDist = 0, leftBackDist = 0;

double movingAvgLeftFront[10];
double movingAvgLeftBack[10];
double movingAvgLeftFrontV=0, movingAvgLeftBackV=0;


long frontLeftDur = 0, frontRightDur = 0;
long frontLeftDist = 0, frontRightDist = 0;

double movingAvgFrontLeft[10];
double movingAvgFrontRight[10];
double movingAvgFrontLeftV=0, movingAvgFrontRightV=0;

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data
double gyroZ = 0, gyroZangle = 0;

long start_i;
int stop_b = -1;
int stage = s_clean1LeftSAllign;
//int stage = s_stop;
void calc_correction(int dir, int sensor, int shiftRef, double angleRef = 0);
void allign(int sensor, double angleRef = 0.0);


void setup() {
  Serial.begin (9600);

//  pinMode(encoderPinRight1, INPUT); 
//  pinMode(encoderPinRight2, INPUT);
//  pinMode(encoderPinLeft1, INPUT); 
//  pinMode(encoderPinLeft2, INPUT);
  pinMode(leftFrontTrigPin, OUTPUT); 
  pinMode(leftFrontEchoPin, INPUT); 
  pinMode(leftBackTrigPin, OUTPUT); 
  pinMode(leftBackEchoPin, INPUT);
  pinMode(frontLeftTrigPin, OUTPUT); 
  pinMode(frontLeftEchoPin, INPUT); 
  pinMode(frontRightTrigPin, OUTPUT); 
  pinMode(frontRightEchoPin, INPUT);

//  digitalWrite(encoderPinRight1, HIGH); //turn pullup resistor on
//  digitalWrite(encoderPinRight2, HIGH); //turn pullup resistor on
//  digitalWrite(encoderPinLeft1, HIGH); //turn pullup resistor on
//  digitalWrite(encoderPinLeft2, HIGH); //turn pullup resistor on

  
//  attachInterrupt(5, updateEncoderRight, CHANGE); 
//  attachInterrupt(4, updateEncoderRight, CHANGE);
//  attachInterrupt(3, updateEncoderLeft, CHANGE); 
//  attachInterrupt(2, updateEncoderLeft, CHANGE);
  init_imu();
  init_ultra();
//  leftRefDist = leftBackDist;
}


void loop(){
  serial_print();
  
  if(stage == s_clean1LeftSAllign){
    serial_twoln("Chutiya:\t", stage);
    allign(left, 0.0);
    read_ultra();
    find_moving_avg();
    leftRefDist = movingAvgLeftBackV;
    stage = s_clean1LeftS;
  }
  else if(stage == s_clean1LeftS){
    serial_twoln("Chutiya:\t", stage);
    if (frontRightDist > sc_clean1FrontSStopDist){
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
      stage = s_clean1FrontSB;
      delay(1000);
      recalibrate();
    }
  }
  else if(stage == s_clean1FrontSB){
    serial_twoln("Chutiya:\t", stage);
    if (frontRightDist < sc_clean1FrontSStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(backward, front, -1);
      apply_correction(backward);
    }
    else{
//      apply_correction(0);
      stage = s_clean1LeftSB;
      recalibrate();
    }
  }
  else if(stage == s_clean1LeftSB){
    serial_twoln("Chutiya:\t", stage);
    if (frontLeftDist < sc_clean1LeftSStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(backward, left, leftRefDist);
      apply_correction(backward);
    }
    else{
      apply_correction(0);
      delay(500);
      allign(left, 0);
      delay(1000);
      sv_clean1FrontStop = frontRightDist-87.63+frontLeftOmniDist;
      stage = s_clean1LeftSRotSlight;
    }
  }
  else if(stage == s_clean1LeftSRotSlight){
    serial_twoln("Chutiya:\t", stage);
    allign(left, sc_clean1LeftSRotAngle);
    stage = s_clean1LeftSTilt;
    delay(1000);
    calc_correction(forward, left, -1);
    sv_clean1LeftStopF = leftBackOmniDist*(1-tan(angleError*3.14/180))+sv_clean1FrontStop*tan(angleError*3.14/180)/cos(angleError*3.14/180)+leftBackDist-29;

  }
  else if(stage == s_clean1LeftSTilt){
    serial_twoln("Chutiya:\t", stage);
    if (leftBackDist < sv_clean1LeftStopF){
      read_ultra();
      find_moving_avg();
      correction = 0;
      apply_correction(forward);
    }
    else{
      apply_correction(0);
      stage = s_clean1LeftSAllign2;
      delay(1000);  
    }
  }

  else if(stage == s_clean1LeftSAllign2){
    serial_twoln("Chutiya:\t", stage);
    read_ultra();
    find_moving_avg();
    rotate_imu(c_anticlockwise, angleError);
    allign(left, 0.0);
    recalibrate();
    stage = s_clean1F;
  }

  else if(stage == s_clean1F){
    serial_twoln("Chutiya:\t", stage);
    if (frontRightDist > marginDist+20){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, front, -1);
      apply_correction(forward);
    }
    else
      stage = s_clean122;
  }

  else if(stage == s_clean122){
    serial_twoln("Chutiya:\t", stage);
    read_ultra();
    find_moving_avg();
    serial_print();
    rotate_imu(c_clockwise, 90);
    delay(400);
    recalibrate();
    allign(left, 0);
    stage = s_clean2F;
  }

  else if(stage == s_clean2F){
    serial_twoln("Chutiya:\t", stage);
    if (frontLeftDist > 125){
      read_ultra();
      find_moving_avg();
      correction = 0;
      apply_correction(forward);  
    }
    else{
      stage = s_clean2R;
    }
  }

  else if(stage == s_clean2R){
    serial_twoln("Chutiya:\t", stage);
    rotate_imu(c_clockwise, 90);
    delay(200);
    recalibrate();
    allign(front, 0);
    delay(500);
    recalibrate();
    stage = s_clean2P;
  }

  else if(stage == s_clean2P){
    serial_twoln("Chutiya:\t", stage);
    if (frontLeftDist > marginDist+30){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, front, -1);
      apply_correction(forward); 
    }
    else
      stage = s_clean223R;
  }

  else if(stage == s_clean223R){
    serial_twoln("Chutiya:\t", stage);
    rotate_imu(c_anticlockwise, 90);
    delay(300);
    recalibrate();
    allign(front, 0);
    delay(200);
    recalibrate();
    stage = s_clean223F;
  }

  else if(stage == s_clean223F){
    serial_twoln("Chutiya:\t", stage);
    if (frontLeftDist > 80){
      read_ultra();
      find_moving_avg();
      correction = 0;
      apply_correction(forward);
    }
    else{
      stage = s_clean223R2;
      apply_correction(0);
    }
  }

  else if(stage == s_clean223R2){
    serial_twoln("Chutiya:\t", stage);
    rotate_imu(c_anticlockwise, 90);
    delay(200);
    recalibrate();
    allign(left, 0);
    delay(200);
    recalibrate();
    stage = s_clean3F;
  }

  else if(stage == s_clean3F){
    serial_twoln("Chutiya:\t", stage);
     if (frontRightDist > 75){
      read_ultra();
      find_moving_avg();
      correction = 0;
      apply_correction(forward);
     }
     else
      stage = s_clean32CR; 
  }

  else if(stage == s_clean32CR){
    serial_twoln("Chutiya:\t", stage);
    recalibrate();
    rotate_imu(c_anticlockwise, 90);
    delay(500);
    allign(left, 0);
    delay(500);
    stage = s_stop;
  }

  
  else if (stage == s_stop){
    serial_twoln("Chutiya:\t", stage);
    apply_correction(0);
    while (1){
      read_ultra();
      find_moving_avg();
//      read_imu();
      calc_correction(forward, left, leftRefDist);
      serial_print();
    }
  }
      
//  read_ultra();
//  find_moving_avg();
  serial_print();
}

