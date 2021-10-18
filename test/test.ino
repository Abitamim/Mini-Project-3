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
const int RIGHT_SENSOR_CAL = 36;
const int LEFT_SENSOR_CAL = 36;
int rightSpeed = 150;
int leftSpeed = 150;
int slowerSpeed = rightSpeed - 10;

int nextMove;

void setup() {
    
    pinMode(SENSOR_ONE, INPUT);
    pinMode(SENSOR_TWO, INPUT);
    Serial.begin(57600);
    AFMS.begin();
    LeftMotor->setSpeed(leftSpeed);
    RightMotor->setSpeed(rightSpeed);
    
}

void loop() {
    Serial.println("SENSOR 1: " + String(analogRead(SENSOR_ONE)));
    Serial.println("SENSOR 2: " + String(analogRead(SENSOR_TWO)));
    delay(500);
    nextMove = findNextMove();
    Serial.println("Next move: " + String(nextMove)); 
    switch (nextMove) {
      case 0:
        Serial.println("Turning Left");
        turnLeft(100);
      case 1:
        Serial.println("Moving forward");
        moveForward(100);
      case 2:
        Serial.println("Turning Right");
        turnRight(100);
    }
}

//Returns 1 for straight, 0 for left, 2 for right
int findNextMove() {
  rightSensorVal = analogRead(SENSOR_ONE);
  leftSensorVal = analogRead(SENSOR_TWO);
  //returns an int 0, 1, or 2
  if (rightSensorVal <= RIGHT_SENSOR_CAL && leftSensorVal <= RIGHT_SENSOR_CAL)
    return 1; //
  if (rightSensorVal > RIGHT_SENSOR_CAL) {
    return 2;
  }
  return 0;
}

void moveForward(int ticks) {
  LeftMotor->run(FORWARD);
  RightMotor->run(FORWARD);
  delay(ticks);
  LeftMotor->run(RELEASE); 
  RightMotor->run(RELEASE);
}

void turnLeft(int ticks) {
  LeftMotor->setSpeed(slowerSpeed);
  LeftMotor->run(FORWARD);
  RightMotor->run(FORWARD);
  delay(ticks);
  LeftMotor->run(RELEASE); 
  RightMotor->run(RELEASE);
}

void turnRight(int ticks) {
  RightMotor->setSpeed(slowerSpeed);
  RightMotor->run(FORWARD);
  LeftMotor->run(FORWARD);
  delay(ticks);
  LeftMotor->run(RELEASE); 
  RightMotor->run(RELEASE);
}
