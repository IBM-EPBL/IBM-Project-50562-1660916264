#include <Servo.h>

// Acts as both trig(input) and echo(output) of the Ultrasonic sensor
const int US_PIN = 12;
Servo doorServo;
const int DS_PIN = 9;
const int SMOKE_PIN = A5;
const int PIEZO_PIN = 8;
const int PIR_PIN = 7;
const int FAN_OFF_PIN = 6;
const int FAN_ON_PIN = 5;
const int FAN_SWITCH_PIN = 4;
const int LDR_PIN = A4;
const int LIGHT_PIN = 3;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(FAN_SWITCH_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(PIEZO_PIN, OUTPUT);
  pinMode(FAN_ON_PIN, OUTPUT);
  pinMode(FAN_OFF_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  
  doorServo.write(0);
  doorServo.attach(DS_PIN);

  Serial.begin(9600);
}

double getDistanceOfObject() {
  pinMode(US_PIN, OUTPUT);
  
  // Clear trig pin
  digitalWrite(US_PIN, LOW);
  delayMicroseconds(2);
  
  // Set trig pin to HIGH for 10 Microseconds to trigger the
  // sensor to emit an 8 cycle sonic pulse that travels at the
  // speed of sound (343 m/s) or (343 * 10^-4 cm/microseconds)
  digitalWrite(US_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_PIN, LOW);

  // Start the timer and stop when the incoming pulse turns HIGH
  pinMode(US_PIN, INPUT);
  unsigned long duration = pulseIn(US_PIN, HIGH); // Microseconds
  
  // 2 * s = v * t
  return (0.0344 * duration) / 2;
}

void automateDoor() {
  double distance = getDistanceOfObject();
  if (distance < 50) {
  	doorServo.write(90);
  } else {
  	doorServo.write(0);
  }
}

void detectSmoke() {
  int smokeVal = analogRead(SMOKE_PIN);
  if (smokeVal > 200) {
  	digitalWrite(PIEZO_PIN, HIGH);
  } else {
    digitalWrite(PIEZO_PIN, LOW);
  }
}

void automateFan() {
  bool fanState = digitalRead(PIR_PIN) || digitalRead(FAN_SWITCH_PIN);
  digitalWrite(FAN_ON_PIN, fanState);
  digitalWrite(FAN_OFF_PIN, !fanState);
  
  delayMicroseconds(10);
}

void automateLight() {
  double ldrValue = analogRead(LDR_PIN);
  if (ldrValue > 500) {
  	digitalWrite(LIGHT_PIN, LOW);
  } else {
  	digitalWrite(LIGHT_PIN, digitalRead(PIR_PIN));
  }
}

void loop() {  
  pinMode(US_PIN, OUTPUT);
  
  automateDoor();
  detectSmoke();
  automateFan();
  automateLight();
}