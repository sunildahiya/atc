void calc_coord(){
  double rightDistTrav = 2*PI*wheelRadius*(encoderValueRight - prevEncoderValueRight)/245;
  double leftDistTrav = 2*PI*wheelRadius*(encoderValueLeft - prevEncoderValueLeft)/245;
  double midDistTrav = (rightDistTrav+leftDistTrav)/2;

  double angleChange = (leftDistTrav-rightDistTrav)/wheelSeparation;
  angle = angle + angleChange;
  
  x = midDistTrav*sin(angle);
  y = midDistTrav*cos(angle);

  prevEncoderValueRight = encoderValueRight;
  prevEncoderValueLeft = encoderValueLeft;
  }
