void calc_coord(){
  double rightDistTrav = encoderValueRight - prevEncoderValueRight;
  double leftDistTrav = encoderValueLeft - prevEncoderValueLeft;
  prevEncoderValueRight = encoderValueRight;
  prevEncoderValueLeft = encoderValueLeft;
  
  rightDistTrav = 2*PI*wheelRadius*rightDistTrav/977;
  leftDistTrav = 2*PI*wheelRadius*leftDistTrav/977;
  double midDistTrav = (rightDistTrav+leftDistTrav)/2;

  double angleChange = (leftDistTrav-rightDistTrav)/wheelSeparation;
  angle = angle + angleChange;
  
  x = x + midDistTrav*sin(angle);
  y = y + midDistTrav*cos(angle);
  }
