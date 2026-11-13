#include <Servo.h>

// --- Pin Definitions ---
// L298N Motor Driver
const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;

// IR Flame Sensors
const int sensorLeft = A0;
const int sensorCenter = A1;
const int sensorRight = A2;

// Actuators
const int pumpPin = 8;
const int servoPin = 10;

Servo nozzleServo;

// Most standard LM393 flame sensors output LOW when a fire is detected.
// Change this to HIGH if your specific sensors work inversely.
const int FIRE_DETECTED = LOW; 

void setup() {
  // Motor Setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Actuator Setup
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW); // Ensure pump is off initially
  
  nozzleServo.attach(servoPin);
  nozzleServo.write(90); // Center the nozzle

  // Sensor Setup
  pinMode(sensorLeft, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRight, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Read sensor states
  int leftFire = digitalRead(sensorLeft);
  int centerFire = digitalRead(sensorCenter);
  int rightFire = digitalRead(sensorRight);

  // Decision Logic
  if (centerFire == FIRE_DETECTED) {
    stopMotors();
    extinguishFire();
  } 
  else if (leftFire == FIRE_DETECTED) {
    turnLeft();
  } 
  else if (rightFire == FIRE_DETECTED) {
    turnRight();
  } 
  else {
    // Stop the robot if no fire is detected (or replace with moveForward() to roam)
    stopMotors(); 
  }
  
  delay(100);
}

// --- Movement Functions ---

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// --- Firefighting Function ---

void extinguishFire() {
  digitalWrite(pumpPin, HIGH); // Turn on water pump
  
  // Sweep servo left and right
  for (int angle = 60; angle <= 120; angle += 5) {
    nozzleServo.write(angle);
    delay(50);
  }
  for (int angle = 120; angle >= 60; angle -= 5) {
    nozzleServo.write(angle);
    delay(50);
  }
  
  nozzleServo.write(90); // Return to center
  digitalWrite(pumpPin, LOW); // Turn off water pump
}
