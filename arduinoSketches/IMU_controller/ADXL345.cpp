
#include "ADXL345.h"

// Get Accelerometer Data
void ADXL345::getAccelerometerValues(long* array){
  array[0] = x;
  array[1] = y;
  array[2] = z;
}

// Update Accelerometer Values
void ADXL345::updateAccelValues(){
  unsigned char x_l, y_l, z_l, x_h, y_h, z_h;

  x_l = readRegister(DATAX0);
  x_h = readRegister(DATAX1);
  y_l = readRegister(DATAY0);
  y_h = readRegister(DATAY1);
  z_l = readRegister(DATAZ0);
  z_h = readRegister(DATAZ1);
  
  x = x_l | (x_h << 8);
  y = y_l | (y_h << 8);
  z = z_l | (z_h << 8);
}


// Update Accelerometer Values with Repeated Start
void ADXL345::updateAccelValuesWithRepeatedStart(){
  unsigned char byteArray[6];
  readSequentialRegisters(DATAX0, byteArray, 6);
  
  x = byteArray[0] | (byteArray[1] << 8);
  y = byteArray[2] | (byteArray[3] << 8);
  z = byteArray[4] | (byteArray[5] << 8);
}

// Read Sequential Registers
void ADXL345::readSequentialRegisters(unsigned char firstReg, unsigned char* byteArray, int n){
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(firstReg); // read First Register
  Wire.endTransmission();

  Wire.requestFrom(DEVICE_ADDRESS, n);
  while(Wire.available() < n){}
  for (int i=0; i<n; i++){
    byteArray[i] = Wire.read();
  }
}


// Write to Register
int ADXL345::writeRegister(int reg, unsigned char value) {
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  return Wire.endTransmission();
}

// Read Register
unsigned char ADXL345::readRegister(int reg){
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(DEVICE_ADDRESS,1);
  while(Wire.available() < 1){}
  return Wire.read();
}


// Setup Accelerometer
void ADXL345::setupAccel() {
  //            REG     bit# 76543210
  writeRegister(POWER_CTL, 0b00000000); // Ensure it has default settings
  writeRegister(POWER_CTL, 0b00000100); // Enable sleep mode
  writeRegister(POWER_CTL, 0b00001000); // Enable measure mode
}


// Print CSV
void ADXL345::print_CSV(){
  Serial.print("ACCEL:  ");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(z);
}
