void updateEncoderRight(){
  int MSB = digitalRead(encoderPinRight1); //MSB = most significant bit
  int LSB = digitalRead(encoderPinRight2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncodedRight << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValueRight ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValueRight --;

  lastEncodedRight = encoded; //store this value for next time
}

void updateEncoderLeft(){
  int MSB = digitalRead(encoderPinLeft1); //MSB = most significant bit
  int LSB = digitalRead(encoderPinLeft2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncodedLeft << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValueLeft ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValueLeft --;

  lastEncodedLeft = encoded; //store this value for next time
}
