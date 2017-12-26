#include <Servo.h>
#include <Driver.h>
#include <Fuzzy.h>

//Constants
#define wheelSeparation 39
#define wheelRadius 5
#define leftUltraDist 64  
#define frontUltraDist 47  
#define forward 1
#define backward -1
#define front 1
#define left -1
double leftRefDist = 25;
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
 
//Motor Driver Objects
Driver motorRight(motorRightDirPin1, motorRightDirPin2, motorRightEnPin);
Driver motorLeft(motorLeftDirPin1, motorLeftDirPin2, motorLeftEnPin);

//Fuzzy
//Fuzzy fuzzy(12, 5, 40, 0); //error, derror, correction and centre

double kp = 7, kd = 2;
double error = 0, derror = 0, prevError = 0, correction = 0;
double xError = 0, angleError = 0;
int basePWM = 120;

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
//  calc_coord();
//  apply_correction(1);
  read_ultra();
  find_moving_avg();
  calc_correction(backward, front, leftRefDist);
  apply_correction(backward);
  
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

