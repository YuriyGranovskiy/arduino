#include <IRremote.h>

int RIGHT_WHEELS_1_PIN = 5;
int RIGHT_WHEELS_2_PIN = 6;
int LEFT_WHEELS_1_PIN = 9;
int LEFT_WHEELS_2_PIN = 10;

int OBSTACLE_FRONT_PIN = 12;
int OBSTACLE_RIGHT_PIN = 2;
int OBSTACLE_LEFT_PIN = 7;

int IR_RECV_PIN = 8;

int robotMode = 0; // 0 - direct, 1 - obstacle, 2 - program
bool isMoving = 0;

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
      robotMode = (robotMode + 1) % 3;
      Serial.println(robotMode);
    }
  }

  switch (robotMode) {
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

  delay(200);
}

void movingByProgram() {

}

void movingByRemote(int remoteValue) {
  int canMoveFront = digitalRead(OBSTACLE_FRONT_PIN);
  int canMoveRight = digitalRead(OBSTACLE_RIGHT_PIN);
  int canMoveLeft = digitalRead(OBSTACLE_LEFT_PIN);
  Serial.println(canMoveFront);
    
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
      if(isMoving = 1) {
        if(canMoveFront == 1 && canMoveLeft == 1) {        
          turnLeftWhileMoving();          
        } else {
          stopMoving();
        }        
      } else {        
        turnLeft();
      }
      break;
    case RIGHT:
      if(isMoving) {
        if(canMoveFront == 1 && canMoveRight == 1) {
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

void moveForward() {
  isMoving = 1;
  analogWrite(RIGHT_WHEELS_1_PIN, 80);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  analogWrite(LEFT_WHEELS_1_PIN, 80);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}

void moveBackward() {
  isMoving = 1;
  digitalWrite(RIGHT_WHEELS_1_PIN, LOW);
  analogWrite(RIGHT_WHEELS_2_PIN, 80);
  digitalWrite(LEFT_WHEELS_1_PIN, LOW);
  analogWrite(LEFT_WHEELS_2_PIN, 80);
}

void turnRight() {
  digitalWrite(RIGHT_WHEELS_1_PIN, LOW);
  analogWrite(RIGHT_WHEELS_2_PIN, 80);
  analogWrite(LEFT_WHEELS_1_PIN, 80);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}

void turnLeft() {
  analogWrite(RIGHT_WHEELS_1_PIN, 80);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  digitalWrite(LEFT_WHEELS_1_PIN, LOW);
  analogWrite(LEFT_WHEELS_2_PIN, 80);
}

void turnLeftWhileMoving() {
  analogWrite(RIGHT_WHEELS_1_PIN, 100);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  analogWrite(LEFT_WHEELS_1_PIN, 50);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}


void turnRightWhileMoving() {
  analogWrite(RIGHT_WHEELS_1_PIN, 50);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  analogWrite(LEFT_WHEELS_1_PIN, 100);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}

void stopMoving() {
  isMoving = 0;
  digitalWrite(RIGHT_WHEELS_1_PIN, LOW);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  digitalWrite(LEFT_WHEELS_1_PIN, LOW);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}
