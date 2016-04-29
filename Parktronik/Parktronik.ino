#include <Arduino.h>

int echoPin = 9;
int triggerPin = 8;
int piezoPin = 12;

void setup() {
    Serial.begin(9600);
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    int duration, cm;
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    cm = duration / 58;
    Serial.print(cm);
    Serial.println(" cm");
    if (cm < 20 && cm > 0) {
         digitalWrite(piezoPin, HIGH);
         delay(300);
         digitalWrite(piezoPin, LOW);
         delay(3000);
    }

    delay(300);
}
