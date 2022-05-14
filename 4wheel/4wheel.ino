#include <IRremote.h>
#include <Wire.h>
#include "4wheel_drive.h"
#include "4wheel_gyro.h"

const int IR_RECV_PIN = 8;

int RobotMode = 2; // 0 - direct, 1 - obstacle, 2 - program

// Numbers - 45,46,47,44,40,43,7,15,9
// # - D

#define OK_BUTTON 0x1C
#define FORWARD 0x18
#define BACKWARD 0x52
#define LEFT 0x08
#define RIGHT 0x5A
#define STAR 0x16

#define DIRECT_MODE 0
#define OBSTACLE_MODE 1
#define PROGRAMMING_MODE 2

int remoteValue = STAR;

IRrecv irrecv(IR_RECV_PIN);

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(RIGHT_WHEELS_1_PIN, OUTPUT);
  pinMode(RIGHT_WHEELS_2_PIN, OUTPUT);
  pinMode(LEFT_WHEELS_1_PIN, OUTPUT);
  pinMode(LEFT_WHEELS_2_PIN, OUTPUT);
  pinMode(OBSTACLE_FRONT_PIN, INPUT);
  pinMode(OBSTACLE_LEFT_PIN, INPUT);
  pinMode(OBSTACLE_RIGHT_PIN, INPUT);
  irrecv.enableIRIn();
}

void loop() {  
  if (irrecv.decode()) {
    remoteValue = irrecv.decodedIRData.command;
    if (remoteValue == OK_BUTTON) {
      stopMoving();
      RobotMode = (RobotMode + 1) % 3;
      Serial.println(RobotMode);
    }
  }

  switch (RobotMode) {
    case DIRECT_MODE:
      movingByRemote(remoteValue);
      break;
    case OBSTACLE_MODE:
      movingWithObstacle();
      break;
    case PROGRAMMING_MODE:
      movingByProgram();
      break;
  }

  Serial.println(remoteValue, HEX);
  irrecv.resume();
}

void turnAngle(float angle) {
  gyro_delay(1);
  float angleStart = Angle;
  float angleEnd = angleStart + angle;
  do {
    if (angleEnd > angleStart) {
      turnLeft();
      gyro_delay(5);
      stopMoving();
    }
    else {
      turnRight();
      gyro_delay(5);
      stopMoving();
    }    
  } while (abs(angleEnd-Angle) > 1);

  if(abs(angleEnd-Angle) > 1) {
    turnAngle(Angle-angleEnd);
  }
}

void movingByProgram() {
  stepsForward(5);
  turnLeft90();
  stepsForward(2);
  turnLeft90();
  stepsForward(4);
  turnLeft90();
  stepsForward(2);
  turnRight90();
  stepForward();
  turnRight90();
  turnRight90();
  
  /*turnLeft90();
  turnLeft90();
  turnLeft90();
  turnLeft90();
  gyro_delay(1000);
  turnRight90();
  turnRight90();
  turnRight90();
  turnRight90();
  gyro_delay(1000);*/
}

void stepForward() {
  moveDuringTime(2300);
  gyro_delay(1000);  
}

void stepsForward(int steps) {
  for(int i = 0; i < steps; i++) {
    stepForward();
  }
}

void turnLeft90() {
  turnAngle(90);
  gyro_delay(1000);
}

void turnRight90() {
  turnAngle(-90);
  gyro_delay(1000);
}

void moveDuringTime(int timeToMove) {
  unsigned long startTime = micros();
  unsigned long endTime = startTime + (long)timeToMove * 1000;
  gyro_delay(1);
  float startAngle = Angle;
  do {
    if (Angle > startAngle + 1) {
      tangleRightWhileMoving();
    } else if (Angle < startAngle - 1) {
      tangleLeftWhileMoving();
    } else {
      moveForward();
    }
    
    gyro_delay(5);
    stopMoving();  
  } while (micros() < endTime);
  stopMoving();
}

void movingByRemote(int remoteValue) {
  int canMoveFront = digitalRead(OBSTACLE_FRONT_PIN);
  int canMoveRight = digitalRead(OBSTACLE_RIGHT_PIN);
  int canMoveLeft = digitalRead(OBSTACLE_LEFT_PIN);
  
  switch (remoteValue) {
    case FORWARD:
      if (canMoveFront == 1) {
        moveForward();
      } else {
        stopMoving();
      }
      break;
    case BACKWARD:
      moveBackward();
      break;
    case LEFT:
      if (IsMoving = 1) {
        if (canMoveFront == 1 && canMoveLeft == 1) {
          turnLeftWhileMoving();
        } else {
          stopMoving();
        }
      } else {
        turnLeft();
      }
      break;
    case RIGHT:
      if (IsMoving) {
        if (canMoveFront == 1 && canMoveRight == 1) {
          turnRightWhileMoving();
        }
        else {
          stopMoving();
        }
      } else {
        turnRight();
      }
      break;
    case STAR:
      stopMoving();
      break;
  }
}

void movingWithObstacle() {
  int canMoveFront = digitalRead(OBSTACLE_FRONT_PIN);
  int canMoveRight = digitalRead(OBSTACLE_RIGHT_PIN);
  int canMoveLeft = digitalRead(OBSTACLE_LEFT_PIN);

  if (canMoveFront == 1 && canMoveRight == 1 && canMoveLeft == 1) {
    moveForward();
  } else {
    if (canMoveRight == 0 && canMoveLeft == 1) {
      turnLeft();
    } else {
      turnRight();
    }

    delay(100);
  }
}
