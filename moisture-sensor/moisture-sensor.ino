#include <Arduino.h>

int sensor1Sig = A0;
int sensor2Sig = A2;
int sensor1Power = 13;
int sensor2Power = 12;

void setup() {
  Serial.begin(9600);

  pinMode(sensor1Power, OUTPUT);
  pinMode(sensor2Power, OUTPUT);
  digitalWrite(sensor1Power, LOW);
  digitalWrite(sensor2Power, LOW);
}

void loop() {
  int sensor1Value = ReadSeveralTimes(sensor1Sig, sensor1Power);
  int sensor2Value = ReadSeveralTimes(sensor2Sig, sensor2Power);

  SendToSerial(sensor1Value, sensor2Value);
  delay(3600000);
}

int ReadSeveralTimes(int signalPin, int sensorPower) {
  int maxIndex = 0;
  int minIndex = 0;
  int maxValue;
  int minValue;
  int currentValue;
  int values[5];

  for(int i = 0; i < 5; i++) {
    digitalWrite(sensorPower, HIGH);
    delay(2000);

    currentValue = analogRead(signalPin);
    values[i] = currentValue;
    if (i == 0) {
      maxValue = currentValue;
      minValue = currentValue;
    }
    else {
      if (currentValue > maxValue)
      {
        maxIndex = i;
        maxValue = currentValue;
      }

      if (currentValue < minValue)
      {
        minIndex = i;
        minValue = currentValue;
      }
    }

    digitalWrite(sensorPower, LOW);
    delay(5000);
  }

  int sum;
  for (int i = 0; i < 5; i++) {
    if (i != maxIndex && i != minIndex) {
        sum += values[i];
    }
  }

  return maxIndex != minIndex ? sum / 3 : sum / 4;
}

void SendToSerial(int sensor1Value, int sensor2Value)
{
  Serial.print("[");
  Serial.print(sensor1Value);
  Serial.print(",");
  Serial.print(sensor2Value);
  Serial.println("]");
}
