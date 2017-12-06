//Constants
#define wheelSeparation 0.5
#define wheelRadius 0.05

//Encoder Interrupt Pins
#define encoderPinRight1 2
#define encoderPinRight2 3
#define encoderPinLeft1 18
#define encoderPinLeft2 19

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

  attachInterrupt(0, updateEncoderRight, CHANGE); 
  attachInterrupt(1, updateEncoderRight, CHANGE);
  attachInterrupt(2, updateEncoderLeft, CHANGE); 
  attachInterrupt(3, updateEncoderLeft, CHANGE);
  
}

void loop(){ 
  Serial.print(encoderValueRight);
  Serial.print("\t");
  Serial.println(encoderValueLeft);
  Serial.print("\t");
  Serial.println(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(angle);  
}

