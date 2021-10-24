#include <Wire.h>  // Wire library - used for I2C communication
int ADXL345 = 0x53;
int d, speed;
float X_out, Y_out, Z_out;
float pitch, pitchF = 0;
void setup() {
  Serial.begin(19200);
  Wire.begin();
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  delay(10);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}
void loop() {
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  X_out = ( Wire.read() | Wire.read() << 8);
  X_out = (X_out / 256);
  Y_out = ( Wire.read() | Wire.read() << 8);
  Y_out = (Y_out / 256);
  Z_out = ( Wire.read() | Wire.read() << 8);
  Z_out = Z_out / 256;
  pitch = (atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180) / 3 ;
  pitchF = 0.94 * pitchF + 0.06 * pitch;
  Serial.print(0);
  Serial.print("/");
  Serial.println(-pitchF);
  d = analogRead(A1);
  speed = map(d, 0, 1024, 0, 255);

  if (pitchF > 0)
    CCW(speed);
  else
    CW(speed);
}

void CW(int speed) {
  analogWrite(3, speed);   //Orange-p chanel
  digitalWrite(4, HIGH);   //Orange-n chanel
  digitalWrite(6, LOW);    //Greeen-p chanel
  digitalWrite(7, LOW);   //Greeen-n chanel;
}
void CCW(int speed) {
  analogWrite(6, speed);   //Orange-p chanel
  digitalWrite(7, HIGH);   //Orange-n chanel
  digitalWrite(3, LOW);    //Greeen-p chanel
  digitalWrite(4, LOW);   //Greeen-n chanel
}


