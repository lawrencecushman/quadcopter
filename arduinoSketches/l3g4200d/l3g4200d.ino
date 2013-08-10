#include <Wire.h>

// Slave Address
#define DEVICE_ADDRESS 0x69

#define WHO_AM_I      0x0F // Holds the address DEVICE_ADDRESS (default 0x69)
#define CTRL_REG1     0x20 
#define CTRL_REG2     0x21
#define CTRL_REG3     0x22
#define CTRL_REG4     0x23
#define CTRL_REG5     0x24
#define REFERENCE_REG 0x25
#define OUT_TEMP      0x26
#define STATUS_REG    0x27
#define OUT_X_L       0x28
#define OUT_X_H       0x29
#define OUT_Y_L       0x2A
#define OUT_Y_H       0x2B
#define OUT_Z_L       0x2C
#define OUT_Z_H       0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG  0x2F
#define INT1_CFG      0x30
#define INT1_SRC      0x31
#define INT1_TSH_XH   0x32
#define INT1_TSH_XL   0x33
#define INT1_TSH_YH   0x34
#define INT1_TSH_YL   0x35
#define INT1_TSH_ZH   0x36
#define INT1_TSH_ZL   0x37
#define INT1_DURATION 0x38

byte x_l, y_l, z_l, x_h, y_h, z_h;
long x,y,z;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  setupGyro();
}

void loop() {
  updateGyroValuesSequentially();
  print_CSV();
  delay(100);
}

void updateGyroValues(){
  x_l = readRegister(OUT_X_L);
  x_h = readRegister(OUT_X_H);
  y_l = readRegister(OUT_Y_L);
  y_h = readRegister(OUT_Y_H);
  z_l = readRegister(OUT_Z_L);
  z_h = readRegister(OUT_Z_H);
  
  x = x_l | (x_h << 8);
  y = y_l | (y_h << 8);
  z = z_l | (z_h << 8);
}

void updateGyroValuesSequentially(){
  byte* byteArray = readSequentialRegisters(OUT_X_L, 6);
  
  x = byteArray[0] | (byteArray[1] << 8);
  y = byteArray[2] | (byteArray[3] << 8);
  z = byteArray[4] | (byteArray[5] << 8);
}

byte* readSequentialRegisters(byte firstReg, int n){
  byte byteArray[n];
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(firstReg | ( 1 << 7 ));
  Wire.endTransmission();

  Wire.requestFrom(DEVICE_ADDRESS,n);
  while(Wire.available() < n){}
  for (int i=0; i<n; i++){
    byteArray[i] = Wire.read();
  }
  return byteArray;
}

int writeRegister(int reg, byte value) {
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  return Wire.endTransmission();
}

byte readRegister(int reg){
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(DEVICE_ADDRESS,1);
  while(Wire.available() < 1){}
  return Wire.read();
}

void setupGyro() {
  //            REG#    bit# 76543210
  writeRegister(CTRL_REG1, 0b00001111);  // default, but with 200Hz bandwidth and 50Hz cut-off freq.
  writeRegister(CTRL_REG2, 0b00000000);  // TODO: Configure this HPF, currently default
  writeRegister(CTRL_REG3, 0b00000000);  // default
  writeRegister(CTRL_REG4, 0b00000000);  // default, but with 2000dps Full scale, default was 250dps full scale
  writeRegister(CTRL_REG5, 0b00000000);  // default
}

void print_CSV(){
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(z);
}
