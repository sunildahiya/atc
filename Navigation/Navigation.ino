#include <Servo.h>
#include <Driver.h>
#include <Fuzzy.h>

//Constants
#define wheelSeparation 39
#define wheelRadius 5
#define forward 1
#define backward -1

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

//Motor Driver Objects
Driver motorRight(motorRightDirPin1, motorRightDirPin2, motorRightEnPin);
Driver motorLeft(motorLeftDirPin1, motorLeftDirPin2, motorLeftEnPin);

//Fuzzy
//Fuzzy fuzzy(12, 5, 40, 0); //error, derror, correction and centre

double kp = 15, kd = 4;
double error = 0, derror = 0, prevError = 0, correction = 0;
double xError = 0, angleError = 0;
int basePWM = 130;

volatile int lastEncodedRight = 0;
volatile long encoderValueRight = 0;
long prevEncoderValueRight = 0;

volatile int lastEncodedLeft = 0;
volatile long encoderValueLeft = 0;
long prevEncoderValueLeft = 0;

double x = 0, y = 0, angle = 0;

void setup() {
  Serial.begin (9600);

  pinMode(encoderPinRight1, INPUT); 
  pinMode(encoderPinRight2, INPUT);
  pinMode(encoderPinLeft1, INPUT); 
  pinMode(encoderPinLeft2, INPUT);

  digitalWrite(encoderPinRight1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinRight2, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinLeft1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinLeft2, HIGH); //turn pullup resistor on

  
  attachInterrupt(5, updateEncoderRight, CHANGE); 
  attachInterrupt(4, updateEncoderRight, CHANGE);
  attachInterrupt(3, updateEncoderLeft, CHANGE); 
  attachInterrupt(2, updateEncoderLeft, CHANGE);
  
}

void loop(){
  calc_coord();
  apply_correction(1);
  
  Serial.print(encoderValueLeft);
  Serial.print("\t"); 
  Serial.print(encoderValueRight);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(angle);
  Serial.print("\t");  
  Serial.print(error);
  Serial.print("\t");
  Serial.print(derror);
  Serial.print("\t");
  Serial.println(correction);
}

