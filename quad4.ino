#include <Wire.h>
#include <TxRx.h>
#include <Motors.h>
#include <Servo.h> 
#include <I2C.h>
#include <L3G4200D.h>
#include <ADXL345.h>

TxRx txrx;
Motors motors;
L3G4200D gyro;
ADXL345 accel;

Servo frontLeft;
Servo frontRight;
Servo rearLeft;
Servo rearRight;

void setup() 
{
  Wire.begin();
  
  frontLeft.attach(5);
  frontRight.attach(6);
  rearLeft.attach(9);
  rearRight.attach(10);
  
  gyro.SetupL3G4200D(2000);
  accel.SetupADXL345();
  
  Serial.begin(9600);
  Serial.println("initializing");
  
  delay(1500); //for l3g4200d
}
 
void loop()
{ 
  Input();
  Update2();
  Thrust();
  
  delay(10);
}

void Input() {
  //txrx.Receive();
  gyro.UpdateGyroValues();
  accel.UpdateAccelValues();
}

void Update2()
{
  Serial.print("gyro: ");
  Serial.print(gyro.GetX());
  Serial.print(" ");
  Serial.print(gyro.GetY());
  Serial.print(" ");
  Serial.print(gyro.GetZ());
  Serial.print(" accel: ");
  Serial.print(accel.GetX());
  Serial.print(" ");
  Serial.print(accel.GetY());
  Serial.print(" ");
  Serial.println(accel.GetZ());
}

void Update() {
  int roll = 85 - map(txrx.getCh1(), 1500, 2400, 0, 180);
  int pitch = 82 - map(txrx.getCh2(), 1500, 2400, 0, 180);
  int throttle = map(txrx.getCh3(), 1500, 2400, 0, 180);
  int yaw = 82 - map(txrx.getCh4(), 1500, 2400, 0, 180);
  roll /= 8;
  pitch /= 8;
  yaw /= 8;
  if (throttle < 25) { 
    throttle = 25;
    roll = 0;
    pitch = 0;
    yaw = 0;
  }
  
  //float throttle = (float(txrx.Ch3) - 1500) * (180 - 0) / (2400 - 1500) + 0;
  
  //Serial.println(yaw);
  //Serial.print("throttle="); Serial.print(throttle); Serial.print(" ch1="); Serial.print(txrx.getCh1()); Serial.print(" ch2="); Serial.println(txrx.getCh2());
  //Serial.print("throttle="); Serial.print(throttle); Serial.print(" roll="); Serial.print(roll); Serial.print(" pitch="); Serial.println(pitch);
  
  //motors.setFrontLeft(throttle - roll + pitch - yaw);
  //motors.setFrontRight(throttle + roll + pitch + yaw);
  //motors.setRearLeft(throttle - roll - pitch + yaw);
  //motors.setRearRight(throttle + roll - pitch - yaw);
  
  //Serial.print("frontleft="); Serial.print(motors.getFrontLeft()); Serial.print(" frontright="); Serial.print(motors.getFrontRight());
  //Serial.print(" rearleft="); Serial.print(motors.getRearLeft()); Serial.print(" rearright="); Serial.println(motors.getRearRight());
}

void Thrust() {
  frontLeft.write(motors.frontLeft);
  frontRight.write(motors.frontRight);
  rearLeft.write(motors.rearLeft);
  rearRight.write(motors.rearRight);
}