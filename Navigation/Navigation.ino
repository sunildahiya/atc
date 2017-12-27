#include <Servo.h>
#include <Driver.h>
#include <Fuzzy.h>

//Constants
#define wheelSeparation 39
#define wheelRadius 5
#define leftUltraDist 26  
#define frontUltraDist 30  
#define forward 1
#define backward -1
#define front 1
#define left -1
#define c_clockwise 1
#define c_anticlockwise -1
#define rotDur 2400
#define entryDist 130 
#define marginDist 45
#define sc_clean1FrontSStopDist 50
#define sc_clean1LeftSStopDist 100 //To do
#define sc_clean1LeftSRotAngle 18 //To do
#define sc_clean1LeftSTiltDist 26

#define s_entry 1
#define s_clean1LeftSAllign 2
#define s_clean1LeftS 3
#define s_clean1FrontS 4
#define s_clean1FrontSB 5
#define s_clean1LeftSRotSlight 6
#define s_clean1LeftSB 7
#define s_clean1FrontRightSShift 9 
#define s_clean1LeftSRot90 10
#define s_stop 11
#define s_clean1LeftSTilt 12
#define s_clean12clean2 13
double leftRefDist = 18;
double frontRefDist = 25;

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

//Commode Mechanism Motor
#define rackMotorDirPin 28
#define rackMotorEnPin 10
#define commodeMotorDirPin 30
#define commodeMotorEnPin 11

//Motor Driver Objects
Driver motorRight(motorRightDirPin1, motorRightDirPin2, motorRightEnPin);
Driver motorLeft(motorLeftDirPin1, motorLeftDirPin2, motorLeftEnPin);

Driver rackMotor(rackMotorDirPin, rackMotorEnPin);
Driver commodeMotor(commodeMotorDirPin, commodeMotorEnPin);



//Fuzzy
//Fuzzy fuzzy(12, 5, 40, 0); //error, derror, correction and centre

double kp = 2, kd = 0;
double error = 0, derror = 0, prevError = 0, correction = 0;
double xError = 0, angleError = 0;
int basePWM = 180;
int basePWMRotate_d = 120;
int basePWMRotate_s = 160;
volatile int lastEncodedRight = 0;
volatile long encoderValueRight = 0;
long prevEncoderValueRight = 0;

volatile int lastEncodedLeft = 0;
volatile long encoderValueLeft = 0;
long prevEncoderValueLeft = 0;

double x = 0, y = 0, angle = 0;

long leftFrontDur = 0, leftBackDur = 0;
long leftFrontDist = 0, leftBackDist = 0;

double movingAvgLeftFront[10];
double movingAvgLeftBack[10];
double movingAvgLeftFrontV=0, movingAvgLeftBackV=0;


long frontLeftDur = 0, frontRightDur = 0;
long frontLeftDist = 0, frontRightDist = 0;

double movingAvgFrontLeft[10];
double movingAvgFrontRight[10];
double movingAvgFrontLeftV=0, movingAvgFrontRightV=0;

long start_i;
int stop_b = -1;
int stage = s_clean1LeftSAllign;

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

  init_ultra();
}

void loop(){
  if (Serial.available()){
    int v = Serial.read();
//    if (v == 1){
//      rackMotor.clockwise(120);
//      delay(2000);
//      rackMotor.stall();
//    }
//    if (v == 2){
//      rackMotor.anticlockwise(120);
//      delay(2000);
//      rackMotor.stall();
//    }
    commodeMotor.clockwise(160);
  }
}

/*
void loop(){
  Serial.print("Stage:\t");
  Serial.println(stage);
  if(stage == s_clean1LeftSAllign){
    allign(left, 0.0);
    read_ultra();
    find_moving_avg();
//    serial_print();
//    leftRefDist = movingAvgLeftBackV;
    stage = s_clean1LeftS;
  }
  else if(stage == s_clean1LeftS){
    if (movingAvgFrontRightV > sc_clean1FrontSStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, left, leftRefDist);
      apply_correction(forward);
    }
    else
      stage = s_clean1FrontS;
  }
  else if(stage == s_clean1FrontS){
    if (movingAvgFrontRightV > marginDist){
      read_ultra();
      find_moving_avg();
      calc_correction(forward, front, -1);
      apply_correction(forward);
      serial_print();
    }
    else
      stage = s_clean1FrontSB;
  }
  else if(stage == s_clean1FrontSB){
    if (movingAvgFrontRightV < sc_clean1FrontSStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(backward, front, -1);
      apply_correction(backward);
    }
    else{
      stage = s_clean1LeftSB;
      movingAvgLeftFrontV = leftFrontDist;
      movingAvgLeftBackV = leftBackDist;
      for (int i=0; i<10; i++){
        movingAvgLeftFront[i] = leftFrontDist;
        movingAvgLeftBack[i] = leftBackDist;
      }
    }
  }
  else if(stage == s_clean1LeftSB){
    if (movingAvgFrontLeftV < sc_clean1LeftSStopDist){
      read_ultra();
      find_moving_avg();
      calc_correction(backward, left, leftRefDist);
      apply_correction(backward);
    }
    else
      stage = s_clean1LeftSRotSlight;
  }
  else if(stage == s_clean1LeftSRotSlight){
    allign(left, sc_clean1LeftSRotAngle);
//    serial_print();
    stage = s_clean1LeftSTilt;
//    stage = s_stop;
  }
  else if(stage == s_clean1LeftSTilt){
    if (movingAvgLeftBackV < sc_clean1LeftSTiltDist){
      read_ultra();
      find_moving_avg();
//      calc_correction(forward, left, leftRefDist);
      correction = 0;
      apply_correction(forward);
    }
    else
      stage = s_clean12clean2;
  }
  else if(stage == s_clean12clean2){
    rotate_dur(c_clockwise, 1600);
    allign(left, 0);
    stage = s_stop;
  }
//  else if(stage == s_clean1LeftSB){
//    if (movingAvgLeftBackV < sc_clean1LeftSStopDist){
//      read_ultra();
//      find_moving_avg();
//      calc_correction(backward, left, -1);
//      apply_correction(backward);
//    }
//    else
//      stage = s_clean1LeftSAllign;
//  }
//  else if(stage == s_clean1LeftSRot90){
//    rotate_dur(c_clockwise, rotDur);
//    allign(left, 0.0);
//    stage = s_stop;
//  }
  else if (stage = s_stop)
    apply_correction(0);
//  
  serial_print();
}
*/
