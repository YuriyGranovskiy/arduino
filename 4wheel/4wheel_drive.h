const int RIGHT_WHEELS_1_PIN = 5;
const int RIGHT_WHEELS_2_PIN = 6;
const int LEFT_WHEELS_1_PIN = 9;
const int LEFT_WHEELS_2_PIN = 10;

const int OBSTACLE_FRONT_PIN = 12;
const int OBSTACLE_RIGHT_PIN = 2;
const int OBSTACLE_LEFT_PIN = 7;

bool IsMoving = 0;

void moveForward() {
  IsMoving = 1;
  analogWrite(RIGHT_WHEELS_1_PIN, 80);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  analogWrite(LEFT_WHEELS_1_PIN, 80);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}

void moveBackward() {
  IsMoving = 1;
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
  IsMoving = 1;
  analogWrite(RIGHT_WHEELS_1_PIN, 100);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  analogWrite(LEFT_WHEELS_1_PIN, 50);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}


void turnRightWhileMoving() {
  IsMoving = 1;
  analogWrite(RIGHT_WHEELS_1_PIN, 50);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  analogWrite(LEFT_WHEELS_1_PIN, 100);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}

void tangleRightWhileMoving() {
  IsMoving = 1;
  analogWrite(RIGHT_WHEELS_1_PIN, 60);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  analogWrite(LEFT_WHEELS_1_PIN, 90);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}

void tangleLeftWhileMoving() {
  IsMoving = 1;
  analogWrite(RIGHT_WHEELS_1_PIN, 90);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  analogWrite(LEFT_WHEELS_1_PIN, 60);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}

void stopMoving() {
  IsMoving = 0;
  digitalWrite(RIGHT_WHEELS_1_PIN, LOW);
  digitalWrite(RIGHT_WHEELS_2_PIN, LOW);
  digitalWrite(LEFT_WHEELS_1_PIN, LOW);
  digitalWrite(LEFT_WHEELS_2_PIN, LOW);
}