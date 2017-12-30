void init_imu() {
  Wire.begin();
#if ARDUINO >= 157
  Wire.setClock(400000UL);
#else
  TWBR = ((F_CPU / 400000UL) - 16) / 2;
#endif

  i2cData[0] = 7; 
  i2cData[1] = 0x00;
  i2cData[2] = 0x00;
  i2cData[3] = 0x00;
  while (i2cWrite(0x19, i2cData, 4, false));
  while (i2cWrite(0x6B, 0x01, true));

  while (i2cRead(0x75, i2cData, 1));
  if (i2cData[0] != 0x68) {
    Serial.print(F("Error reading sensor"));
    while (1);
  }

  delay(100); // Wait for sensor to stabilize

  while (i2cRead(0x3B, i2cData, 6));
  timer = micros();
}

void read_imu() {
  while (i2cRead(0x3B, i2cData, 14));
  gyroZ = (int16_t)((i2cData[12] << 8) | i2cData[13]);;

  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();
  double gyroZrate = gyroZ / 131.0; // Convert to deg/s
  gyroZangle += gyroZrate * dt;
}
