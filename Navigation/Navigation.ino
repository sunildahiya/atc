#include <Servo.h>
#include <Driver.h>
#include <Fuzzy.h>
#include <Wire.h>
#include <MPU9250.h>

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
#define up 1
#define down -1
#define c_clockwise 1
#define c_anticlockwise -1
#define rotDur 2400
#define entryDist 130 
#define marginDist 20
#define entranceLeftThresh 50
#define entranceFrontThresh 160 //To do
#define sc_clean1LeftSStopDist 60
#define sc_clean1FrontSBStopDist 50
#define sc_clean1LeftSBStopDist 100 
#define sc_clean1LeftSRotAngle 16
#define sc_clean1LeftSTiltDist 16

#define sc_clean1FStopDist 32
#define sc_clean2FStopDist 115
#define sc_clean2PStopDist 40
#define sc_clean3FStopDist 90
#define sc_clean3PStopDist 70
#define sc_cleanCFStopDist 110
#define sc_clean4BStopDist 70
#define sc_clean5BStopDist 70
#define sc_cleanRetFStopDist 30
#define sc_clean4RSlight 15
#define sc_clean5FStopDist 32


#define sc3_clean1FStopDist 55
#define sc3_clean2FLSStopDist 60
#define sc3_cleanRetFStopDist 110

#define s3_clean1F 301
#define s3_clean122 302
#define s3_clean2FLS 303
#define s3_clean2FFS 304
#define s3_clean223 305
#define s3_cleanRetF 306

#define s2_cleanlR 201

#define rackIRPin A0
#define commodeIRPin A1

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


#define s_clean1LeftSAllign2 14
#define s_clean1F 15
#define s_clean122 16
#define s_clean2F 17
//#define s_clean2B 15
#define s_clean2R 18
#define s_clean2P 19
#define s_clean223 20
#define s_clean3F 21
#define s_clean3R 22
#define s_clean3P 23
#define s_clean32C 25
#define s_cleanCB 26

#define s_cleanCommode 27

#define s_cleanCF 28
#define s_cleanC23 29
#define s_clean3P2 30
#define s_clean324 31
#define s_clean4F 32
#define s_clean4RSlight 42
#define s_clean4B 33

#define s_clean425 34

#define s_clean5F 35
#define s_clean5R 36
#define s_clean5P 37
#define s_clean5B 38
#define s_cleanRetR 39
#define s_cleanRetF 40
#define s_cleanRetFinish 41
 
int state = 1;
bool finishStarting = false;

double leftRefDist = 20;
double frontRefDist = 25;
double sv_clean1LeftStopF = 0, sv_clean1LeftStopI = 0, sv_clean1FrontStop = 0;

//Encoder Interrupt Pins
#define encoderPinRight1 18
#define encoderPinRight2 19
#define encoderPinLeft1 20
#define encoderPinLeft2 21

//Motor Driver Pins
#define motorRightEnPin 11
#define motorRightDirPin 30
#define motorLeftEnPin 10
#define motorLeftDirPin 28

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

//Commode Mechanism
#define commodeRackEnPin 44
#define commodeRackDirPin 34
#define commodeCleanEnPin 46
#define commodeCleanDirPin 32

//Floor Mechanism
#define rollerEnPin 4
#define rollerDirPin1 22
#define rollerDirPin2 23
#define mopEnPin 8
#define mopDirPin1 39
#define mopDirPin2 37
 
//Motor Driver Objects
Driver motorRight(motorRightDirPin, motorRightEnPin);
Driver motorLeft(motorLeftDirPin, motorLeftEnPin);

Driver commodeRackMotor(commodeRackDirPin, commodeRackEnPin);
Driver commodeCleanMotor(commodeCleanDirPin, commodeCleanEnPin);

Driver rollerMotor(rollerDirPin1, rollerDirPin2, rollerEnPin);
Driver mopMotor(mopDirPin1, mopDirPin2, mopEnPin);

//Fuzzy
//Fuzzy fuzzy(12, 5, 40, 0); //error, derror, correction and centre

double kp = 10, kd = 1;
double error = 0, derror = 0, prevError = 0, correction = 0;
double xError = 0, angleError = 0;
int basePWM = 130;
int basePWMRotate_d = 120;
int basePWMRotate_imu = 130;
int basePWMRotate_s = 90;

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

int16_t gyro[3] = {0, 0, 0};
MPU9250 jholImu;
double timer = 0;
double gyroZangle = 0;

long start_i;
int stage = s_clean1LeftSAllign;
//int stage = s_stop;
void calc_correction(int dir, int sensor, int shiftRef, double angleRef = 0);
void allign(int sensor, double angleRef = 0.0);

int entranceNo = 1;

void setup() {
  Serial.begin (9600);
 
  pinMode(leftFrontTrigPin, OUTPUT); 
  pinMode(leftFrontEchoPin, INPUT); 
  pinMode(leftBackTrigPin, OUTPUT); 
  pinMode(leftBackEchoPin, INPUT);
  pinMode(frontLeftTrigPin, OUTPUT); 
  pinMode(frontLeftEchoPin, INPUT); 
  pinMode(frontRightTrigPin, OUTPUT); 
  pinMode(frontRightEchoPin, INPUT);
  
  pinMode(commodeIRPin, INPUT);
  pinMode(rackIRPin, INPUT);

  jholImu.initMPU9250();
  timer = micros();
//  gyroZangle = 0;
//  test_imu();
  
  init_ultra();
//  if (leftBackDist < entranceLeftThresh && frontRightDist > entranceFrontThresh)
//    entranceNo = 2;
//  else if(leftBackDist > entranceLeftThresh)
//    entranceNo = 3;
  
//  reset_rack();
//  stage = s3_clean1F;
  Serial.println("Starting......");
}


void loop(){
  
  if (state == 1 && entranceNo == 1)
    clean_state1_ent1();
    
  else if (state == 1 && entranceNo == 2 && !finishStarting)
    clean_state1_ent2();
    
  else if (state == 1 && entranceNo == 2 && finishStarting)
    clean_state1_ent1();

  else if(state == 1 && entranceNo == 3)
    clean_state1_ent3();
    
  else if (state == 2)
    clean_state2();
    
  else if(state == 3 && (entranceNo == 1 || entranceNo == 2))
    clean_state3_ent12();
    
  else if(state == 3 && entranceNo == 3)
    clean_state3_ent3();
    
  else if(state == 4)
    clean_state4();
  
 
//  read_ultra();
//  find_moving_avg();
//  serial_print();

}
