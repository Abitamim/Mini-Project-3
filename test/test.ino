#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const int SENSOR_ONE = A1;
const int SENSOR_TWO = A2;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(2);

int rightSensorVal = 0;
int leftSensorVal = 0;
const int RIGHT_SENSOR_CAL = 500;
const int LEFT_SENSOR_CAL = 500;

void setup() {
    
    pinMode(SENSOR_ONE, INPUT);
    pinMode(SENSOR_TWO, INPUT);
    Serial.begin(57600);
    AFMS.begin();
    LeftMotor->setSpeed(150);
    RightMotor->setSpeed(150);
    
}

void loop() {
    Serial.println("SENSOR 1: " + String(analogRead(SENSOR_ONE)));
    Serial.println("SENSOR 2: " + String(analogRead(SENSOR_TWO)));
    delay(500);
//    LeftMotor->run(FORWARD);
}

int nextMove() {
  rightSensorVal = analogRead(SENSOR_ONE);
  leftSensorVal = analogRead(SENSOR_TWO);
  
}
