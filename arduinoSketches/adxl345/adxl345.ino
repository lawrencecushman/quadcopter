#include <Wire.h>


#define SAD 0x53  // Slave Address Register

// REGISTER MAP
#define WHO_AM_I       0x00 // Holds the value contained in SAD
#define THRESH_TAP     0x1D // 
#define OFSX           0x1E
#define OFSY           0x1F
#define OFSZ           0x20
#define DUR            0x21
#define LATENT         0x22
#define WINDOW         0x23
#define THRESH_ACT     0x24
#define THRESH_INACT   0x25
#define TIME_INACT     0x26
#define ACT_INACT_CTL  0x27
#define THRESH_FF      0x28
#define TIME_FF        0x29
#define TAP_AXES       0x2A
#define ACT_TAP_STATUS 0x2B
#define BW_RATE        0x2C
#define POWER_CTL      0x2D
#define INT_ENABLE     0x2E
#define INT_MAP        0x2F
#define INT_SOURCE     0x30
#define DATA_FORMAT    0x31
#define DATAX0         0x32
#define DATAX1         0x33
#define DATAY0         0x34
#define DATAY1         0x35
#define DATAZ0         0x36
#define DATAZ1         0x37
#define FIFO_CTL       0x38
#define FIFO_STATUS    0x39

byte x_l, y_l, z_l, x_h, y_h, z_h;
long x,y,z;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  setupAccel();
}

void loop() {
  Serial.println(readRegister(DATAX0));
  //updateAccelValues();
  //updateAccelValuesSequentially();
  //print_CSV();
  delay(500);
}

void updateAccelValues(){
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

void updateAccelValuesSequentially(){
  byte* byteArray = readSequentialRegisters(DATAX0, 6);
  
  x = byteArray[0] | (byteArray[1] << 8);
  y = byteArray[2] | (byteArray[3] << 8);
  z = byteArray[4] | (byteArray[5] << 8);
}

byte* readSequentialRegisters(byte firstReg, int n){
  byte byteArray[n];
  Wire.beginTransmission(SAD);
  Wire.write(firstReg);
  Wire.endTransmission();

  Wire.requestFrom(SAD,n);
  while(Wire.available() < n){}
  for (int i=0; i<n; i++){
    byteArray[i] = Wire.read();
  }
  
  return byteArray;
}

int writeRegister(int reg, byte value) {
  Wire.beginTransmission(SAD);
  Wire.write(reg);
  Wire.write(value);
  return Wire.endTransmission();
}

byte readRegister(int reg){
  Wire.beginTransmission(SAD);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(SAD,1);
  while(Wire.available() < 1){}
  return Wire.read();
}

/**---------------------------------------------------------------------------*/
/* Set up the ADXL345
/*   By default, the ADXL345 starts in sleep mode, and needs to be placed
/*   in measure mode to start taking readings. The POWER_CTL register is used
/*   to enable measure mode, but as reccomended by the documentation, we
/*   place the chip in standby mode first.
/**---------------------------------------------------------------------------*/
void setupAccel() {
  
}

void print_CSV(){
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(z);
}
