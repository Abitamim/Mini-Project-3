#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const int SENSOR_ONE = A1;
const int SENSOR_TWO = A2;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(1);

int rightSensorVal = 0;
int leftSensorVal = 0;
const int RIGHT_SENSOR_CAL = 300;
const int LEFT_SENSOR_CAL = 300;
int rightSpeed = 40;
int leftSpeed = 40;
int slowerSpeedRight = 20;
int slowerSpeedLeft = 20;

int nextMove;

void setup() {
    
    pinMode(SENSOR_ONE, INPUT);
    pinMode(SENSOR_TWO, INPUT);
    Serial.begin(9600);
    AFMS.begin();
    LeftMotor->setSpeed(leftSpeed);
    RightMotor->setSpeed(rightSpeed);
    
}

void loop() {
    //Serial.println("SENSOR 1: " + String(analogRead(SENSOR_ONE)));
    //Serial.println("SENSOR 2: " + String(analogRead(SENSOR_TWO)));
    nextMove = findNextMove();
    //Serial.println("Next move: " + String(nextMove)); 
    switch (nextMove) {
      case 0:
        Serial.print(20);
        Serial.print(",");
        Serial.print(-20);
        Serial.print(",");
        Serial.print(analogRead(SENSOR_ONE));
        Serial.print(",");
        Serial.print(analogRead(SENSOR_TWO));
        //Serial.println("Turning Left");
        turnLeft(100);
        break;
      case 1:
        Serial.print(40);
        Serial.print(",");
        Serial.print(40);
        Serial.print(",");
        Serial.print(analogRead(SENSOR_ONE));
        Serial.print(",");
        Serial.print(analogRead(SENSOR_TWO));
        //Serial.println("Moving forward");
        moveForward(100);
        break;
      case 2:
        Serial.print(-20);
        Serial.print(",");
        Serial.print(20);
        Serial.print(",");
        Serial.print(analogRead(SENSOR_ONE));
        Serial.print(",");
        Serial.print(analogRead(SENSOR_TWO));
        //Serial.println("Turning Right");
        turnRight(100);
        break;
    }
    Serial.println();
//    delay(100);
}

//Returns 1 for straight, 0 for left, 2 for right
int findNextMove() {
  rightSensorVal = analogRead(SENSOR_ONE);
  leftSensorVal = analogRead(SENSOR_TWO);
  //returns an int 0, 1, or 2
  if (rightSensorVal <= RIGHT_SENSOR_CAL && leftSensorVal <= RIGHT_SENSOR_CAL)
    return 1; //
  if (rightSensorVal > RIGHT_SENSOR_CAL) {
    return 0;
  }
  return 2;
}

void moveForward(int ticks) {
  RightMotor->setSpeed(rightSpeed);
  LeftMotor->setSpeed(leftSpeed);
  LeftMotor->run(FORWARD);
  RightMotor->run(FORWARD);
//  delay(ticks);
//  LeftMotor->run(RELEASE); 
//  RightMotor->run(RELEASE);
}

void turnLeft(int ticks) {
  LeftMotor->setSpeed(slowerSpeedLeft);
  RightMotor->setSpeed(slowerSpeedRight);
  LeftMotor->run(BACKWARD);
  RightMotor->run(FORWARD);
  delay(ticks);
  LeftMotor->run(RELEASE); 
  RightMotor->run(RELEASE);
}

void turnRight(int ticks) {
  RightMotor->setSpeed(slowerSpeedRight);
  LeftMotor->setSpeed(slowerSpeedRight);
  RightMotor->run(BACKWARD);
  LeftMotor->run(FORWARD);
  delay(ticks);
  LeftMotor->run(RELEASE); 
  RightMotor->run(RELEASE);
}
