
// Copyright (c) 2024 @nnn112358<https://github.com/nnn112358/>

#include <M5Unified.h>
#include "SparkFun_Qwiic_OTOS_Arduino_Library.h"
#include "Wire.h"

QwiicOTOS myOtos;

void setup(){
  auto cfg = M5.config();
  M5.begin(cfg);

  Wire.begin(M5.Ex_I2C.getSDA(), M5.Ex_I2C.getSCL());

  Serial.printf("M5Core2_Qwiic_OTOS_Example");

  while (myOtos.begin() == false)
  {
    M5.Log.printf("I2C not connected, check your wiring and I2C address!");
    delay(1000);
  }

  Serial.printf("OTOS connected!");
  Serial.printf("Ensure the OTOS is flat and stationary, then enter any key to calibrate the IMU");
  Serial.println("Calibrating IMU...");
  Serial.printf(" Calibrate the IMU,resetTracking");
  myOtos.calibrateImu();
  myOtos.resetTracking();
}

void loop(){
  M5.update();

  if (M5.BtnB.wasReleased())
  {
    Serial.printf(" Calibrate the IMU,resetTracking");
    myOtos.calibrateImu();
    myOtos.resetTracking();
  }

  sfe_otos_pose2d_t pos;
  sfe_otos_pose2d_t vel;
  sfe_otos_pose2d_t acc;

  myOtos.getPosition(pos);
  myOtos.getVelocity(vel);
  myOtos.getAcceleration(acc);

  M5.Display.startWrite();
  M5.Display.setCursor(0, 0);
  M5.Display.setTextSize(3);
  M5.Display.printf("x = %+2.2f mm \t\n", pos.x * 25.4);
  M5.Display.printf("y = %+2.2f mm \t\n", pos.y * 25.4);
  M5.Display.printf("th= %+2.2f deg \t\n", pos.h);
  M5.Display.setTextSize(2);

  M5.Display.printf("vx= %+2.2f mm/s \t\n", vel.x * 25.4);
  M5.Display.printf("vy= %+2.2f mm/s \t\n", vel.y * 25.4);
  M5.Display.printf("w = %+2.2f deg/s \t\n", vel.h);
  M5.Display.printf("ax= %+2.2f mm/s2 \t\n", acc.x * 25.4);
  M5.Display.printf("ay= %+2.2f mm/s2 \t\n", acc.y * 25.4);
  M5.Display.printf("aw= %+2.2f deg/s2 \t\n", acc.h);
  M5.Display.endWrite();

  Serial.printf("x = %+.2f mm \t", pos.x * 25.4);
  Serial.printf("y = %+.2f mm \t", pos.y * 25.4);
  Serial.printf("th= %+.2f deg \t", pos.h);
  Serial.printf("vx= %+.2f mm/s \t", vel.x * 25.4);
  Serial.printf("vy= %+.2f mm/s \t", vel.y * 25.4);
  Serial.printf("w = %+.2f deg/s \t", vel.h);
  Serial.printf("ax= %+.2f mm/s2 \t", acc.x * 25.4);
  Serial.printf("ay= %+.2f mm/s2 \t", acc.y * 25.4);
  Serial.printf("aw= %+.2f deg/s2 \t", acc.h);
  Serial.println("");

  delay(10);
}
