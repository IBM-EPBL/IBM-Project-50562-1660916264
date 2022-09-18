#include <Servo.h>


const int smoke_Out = 10;
const int smoke_In = A5;

const int door_Out = 9;
const int door_In = A4;

const int red_Out = 12;
const int green_Out = 13;

int smoke_count = A5;
Servo door;

const int fan = A1;
const int pir = A3;
const int ldr = A2;
const int fan_ON = 4;
const int fan_OFF = 2;
const int light = 7;

void setup()
{
  pinMode(smoke_Out,OUTPUT);
  pinMode(smoke_In,INPUT);

  door.attach(door_Out);
  
  pinMode(light, OUTPUT);
  pinMode(fan_OFF, OUTPUT);
  pinMode(fan_ON, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(ldr, INPUT);
  
  Serial.begin(9600); 
}

void detectSmoke() {
  smoke_count = analogRead(smoke_In);
  if (smoke_count > 500) {
    digitalWrite(smoke_Out, HIGH);
  }
  else {
    digitalWrite(smoke_Out, LOW);
  }
}

long readUSdistance(){
  pinMode(door_In, OUTPUT);
  digitalWrite(door_In, LOW);
  delayMicroseconds(2);
  
  digitalWrite(door_In, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(door_In, LOW);
  pinMode(door_In, INPUT);
  
  return pulseIn(door_In, HIGH); 
}
//DOOR LOGIC
void openDoor() {
  door.write(90);
  digitalWrite(red_Out, LOW);
  digitalWrite(green_Out, HIGH);
}

void closeDoor() {
  door.write(0);
  digitalWrite(red_Out, HIGH);
  digitalWrite(green_Out, LOW);
}

void automateDoor() {
  int distance = 0.01723 * readUSdistance(); //in cms
  if (distance < 50) {
    openDoor();
  }
  else {
    closeDoor();
  }
}


//Fan
void automateFan() {
  bool state = digitalRead(pir) || digitalRead(fan);
  digitalWrite(fan_ON, state);
  digitalWrite(fan_OFF, !state);
  
  delayMicroseconds(10);
  digitalWrite(pir, LOW);
}
//Light
void automateLight() {
  if (analogRead(ldr) < 500) {
    digitalWrite(light, digitalRead(pir));
  }
  else {
    digitalWrite(light, LOW);
  }
  
  delayMicroseconds(10);
  digitalWrite(pir, LOW);
}

void loop()
{
  detectSmoke();
  automateDoor();
  automateFan();
  automateLight();
}
