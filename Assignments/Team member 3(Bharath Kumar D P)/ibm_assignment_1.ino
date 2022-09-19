#include <Servo.h>

int smokeVal = 0;
int smokeOutPin = 0;
int smokeInPin = A0;

int doorOutPin = 4;
int doorInPin = A1;
int servoPin1 = 1;
int servoPin2 = 2;
Servo door;

int fanSwitchPin = A3;
int pirInPin = A2;
int ldrInPin = A4;
int fanGreenPin = 1;
int fanRedPin = 2;
int lightOutPin = 3;

void setup()
{
  pinMode(smokeOutPin,OUTPUT);
  pinMode(smokeInPin,INPUT);

  door.attach(doorOutPin);
  
  pinMode(lightOutPin, OUTPUT);
  pinMode(fanRedPin, OUTPUT);
  pinMode(fanGreenPin, OUTPUT);
  pinMode(pirInPin, INPUT);
  pinMode(ldrInPin, INPUT);
  
  Serial.begin(9600); 
}

void checkSmoke() {
  smokeVal = analogRead(smokeInPin);
  if (smokeVal > 500) {
    digitalWrite(smokeOutPin, HIGH);
  }
  else {
    digitalWrite(smokeOutPin, LOW);
  }
}

long readUltraSonicDistance() {
  pinMode(doorInPin, OUTPUT);
  digitalWrite(doorInPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(doorInPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(doorInPin, LOW);
  pinMode(doorInPin, INPUT);
  
  return pulseIn(doorInPin, HIGH); 
}

void openDoor() {
  door.write(90);
  digitalWrite(servoPin1, LOW);
  digitalWrite(servoPin2, HIGH);
}

void closeDoor() {
  door.write(0);
  digitalWrite(servoPin1, HIGH);
  digitalWrite(servoPin2, LOW);
}

void automateDoor() {
  int distanceCm = 0.01723 * readUltraSonicDistance();
  if (distanceCm < 50) {
    openDoor();
  }
  else {
    closeDoor();
  }
}

void resetPir() {
  digitalWrite(pirInPin, LOW);
}

void automateFan() {
  bool fanState = digitalRead(pirInPin) || digitalRead(fanSwitchPin);
  digitalWrite(fanGreenPin, fanState);
  digitalWrite(fanRedPin, !fanState);
  
  delayMicroseconds(10);
  resetPir();
}

void automateLight() {
  if (analogRead(ldrInPin) < 500) {
    digitalWrite(lightOutPin, digitalRead(pirInPin));
  }
  else {
    digitalWrite(lightOutPin, LOW);
  }
  
  delayMicroseconds(10);
  resetPir();
}

void loop()
{
  checkSmoke();
  automateDoor();
  automateFan();
  automateLight();
}
