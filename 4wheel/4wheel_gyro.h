const int MPU_addr = 0x68;
const long AngleDevider = 69000; // should be 131 but it's not - default 70000

float Angle = 0;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int gyroZCompensation = 24;

int getGyroZ() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
  return GyZ;
}

void gyro_delay(int msDelay){
  unsigned long endTime = micros() + long(msDelay)*1000;
  double gyroZDiff = 0;
  do{
    gyroZDiff += (double)(getGyroZ() - gyroZCompensation) / (double)AngleDevider;
    delayMicroseconds(5);
  } while (micros() < endTime);
  Angle += ((float)(gyroZDiff));    
}

int getGyroZCompensation(){
  unsigned long startTime = micros();
  unsigned long endtime = startTime + 5000000;
  int i = 0;
  long sumGyroZDiff = 0;
  do {
    sumGyroZDiff += getGyroZ();
    delayMicroseconds(50);
    i++;    
  } while (endtime > micros());
  
  return sumGyroZDiff / (long)i;
}