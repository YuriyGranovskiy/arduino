#include <IRremote.hpp>
#include <Wire.h>
#include "4wheel_drive.h"
#include "4wheel_gyro.h"

const int IR_RECV_PIN = 11;

int RobotMode = 0; // 0 - direct, 1 - obstacle, 2 - program

// Numbers - 45,46,47,44,40,43,7,15,9
// # - D

#define OK_BUTTON 0x1C
#define FORWARD 0x18
#define BACKWARD 0x52
#define LEFT 0x08
#define RIGHT 0x5A
#define STAR 0x16
#define BUTTON_1 0x45
#define BUTTON_2 0x46
#define BUTTON_3 0x47


#define DIRECT_MODE 0
#define OBSTACLE_MODE 1
#define ROUTE_MODE 2

int remoteValue = STAR;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  pinMode(RIGHT_WHEELS_1_PIN, OUTPUT);
  pinMode(RIGHT_WHEELS_2_PIN, OUTPUT);
  pinMode(LEFT_WHEELS_1_PIN, OUTPUT);
  pinMode(LEFT_WHEELS_2_PIN, OUTPUT);
  pinMode(OBSTACLE_FRONT_PIN, INPUT);
  pinMode(OBSTACLE_LEFT_PIN, INPUT);
  pinMode(OBSTACLE_RIGHT_PIN, INPUT);
  IrReceiver.begin(IR_RECV_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  bool decoded;
  if (IrReceiver.decode()) {
    decoded = true;
    remoteValue = IrReceiver.decodedIRData.command;
    switch(remoteValue) {
      case OK_BUTTON: {
        stopMoving();
        RobotMode = (RobotMode + 1) % 3;
        break;
      }
      case BUTTON_1: {
        stopMoving();
        RobotMode = DIRECT_MODE;
        break;
      }
      case BUTTON_2: {
        stopMoving();
        RobotMode = OBSTACLE_MODE;
        break;
      }
      case BUTTON_3: {
        stopMoving();
        RobotMode = ROUTE_MODE;
        break;
      }
    }    
  }

  switch (RobotMode) {
    case DIRECT_MODE:
      movingByRemote(remoteValue);
      break;
    case OBSTACLE_MODE:
      movingWithObstacle();
      break;
    case ROUTE_MODE:
      movingByRoute();
      RobotMode = DIRECT_MODE;
      break;
  }

  if(decoded) {
    IrReceiver.resume();
  }
  gyro_delay(100);
}


void movingByRoute() {
  stepsForward(5);
  turnLeft90();
  stepsForward(2);
  turnLeft90();
  stepsForward(4);
  turnLeft90();
  stepsForward(2);
  turnRight90();
  stepForward();
  turnRight180();
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

void stepForward() {
  moveDuringTime(2300);
  gyro_delay(500);  
}

void stepsForward(int steps) {
  for(int i = 0; i < steps; i++) {
    stepForward();
  }
}

void turnLeft90() {
  turnAngle(90);
  gyro_delay(500);
}

void turnLeft1800() {
  turnAngle(180);
  gyro_delay(500);
}

void turnRight90() {
  turnAngle(-90);
  gyro_delay(500);
}

void turnRight180() {
  turnAngle(-180);
  gyro_delay(500);
}

void moveDuringTime(int timeToMove) {
  unsigned long startTime = micros();
  unsigned long endTime = startTime + (long)timeToMove * 1000;
  gyro_delay(1);
  float startAngle = Angle;
  do {
    int canMoveFront = digitalRead(OBSTACLE_FRONT_PIN);
    int canMoveRight = digitalRead(OBSTACLE_RIGHT_PIN);
    int canMoveLeft = digitalRead(OBSTACLE_LEFT_PIN);

    if(canMoveFront == 0 || canMoveRight == 0 || canMoveLeft == 0) {
      RobotMode = DIRECT_MODE;
      return;
    }

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
