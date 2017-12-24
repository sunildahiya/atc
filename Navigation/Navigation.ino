#include <Servo.h>
#include <Driver.h>
#include <Fuzzy.h>

//Constants
#define wheelSeparation 39
#define wheelRadius 5
#define rightUltraDist 76.5  
//#define rightRefDist 25   
#define forward 1
#define backward -1
double rightRefDist = 25;
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

//Ultrasonic Sensors
#define rightFrontTrigPin A5 
#define rightFrontEchoPin A4  
#define rightBackTrigPin A3 
#define rightBackEchoPin  A2 
 
//Motor Driver Objects
Driver motorRight(motorRightDirPin1, motorRightDirPin2, motorRightEnPin);
Driver motorLeft(motorLeftDirPin1, motorLeftDirPin2, motorLeftEnPin);

//Fuzzy
//Fuzzy fuzzy(12, 5, 40, 0); //error, derror, correction and centre

double kp = 10, kd = 0;
double error = 0, derror = 0, prevError = 0, correction = 0;
double xError = 0, angleError = 0;
int basePWM = 30;

volatile int lastEncodedRight = 0;
volatile long encoderValueRight = 0;
long prevEncoderValueRight = 0;

volatile int lastEncodedLeft = 0;
volatile long encoderValueLeft = 0;
long prevEncoderValueLeft = 0;

double x = 0, y = 0, angle = 0;

long rightFrontDur = 0, rightBackDur = 0;
long rightFrontDist = 0, rightBackDist = 0;

double movingAvgRightFront[10];
double movingAvgRightBack[10];
double movingAvgRightFrontV=0, movingAvgRightBackV=0;

void setup() {
  Serial.begin (9600);

  pinMode(encoderPinRight1, INPUT); 
  pinMode(encoderPinRight2, INPUT);
  pinMode(encoderPinLeft1, INPUT); 
  pinMode(encoderPinLeft2, INPUT);
  pinMode(rightFrontTrigPin, OUTPUT); 
  pinMode(rightFrontEchoPin, INPUT); 
  pinMode(rightBackTrigPin, OUTPUT); 
  pinMode(rightBackEchoPin, INPUT);

  digitalWrite(encoderPinRight1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinRight2, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinLeft1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinLeft2, HIGH); //turn pullup resistor on

  
  attachInterrupt(5, updateEncoderRight, CHANGE); 
  attachInterrupt(4, updateEncoderRight, CHANGE);
  attachInterrupt(3, updateEncoderLeft, CHANGE); 
  attachInterrupt(2, updateEncoderLeft, CHANGE);
  for (int i=0; i<5; i++)
    read_ultra();

  rightRefDist = 0;
  for (int i=0; i<50; i++){
    read_ultra();
    rightRefDist += (rightFrontDist+rightBackDist)/2; 
  }
  rightRefDist /= 50;

  movingAvgRightFrontV = 0;
  movingAvgRightBackV = 0;
  for (int i=0; i<10; i++){
    read_ultra();
    movingAvgRightFrontV += rightFrontDist;
    movingAvgRightBackV += rightBackDist;
    movingAvgRightFront[i] = rightFrontDist;
    movingAvgRightBack[i] = rightBackDist;
  }
  movingAvgRightFrontV /= 10;
  movingAvgRightBackV /= 10;
  Serial.println("Setup");
  Serial.print(movingAvgRightFrontV);
  Serial.print("\t");
  Serial.println(movingAvgRightBackV);
//  while(1);
}

void loop(){
  calc_coord();
//  apply_correction(1);
  read_ultra();
  find_moving_avg();
  apply_ultra_correction(-1);
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

  Serial.print(rightFrontDist);
  Serial.print("\t"); 
  Serial.print(rightBackDist);
  Serial.print("\t");
  Serial.print(movingAvgRightFrontV);
  Serial.print("\t"); 
  Serial.print(movingAvgRightBackV);
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
}

