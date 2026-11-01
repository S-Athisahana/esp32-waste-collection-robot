#include <ESP32Servo.h>

// -------- Ultrasonic sensor --------
const int TRIG_PIN = 23;
const int ECHO_PIN = 34;

// -------- Servo motor --------
const int SERVO_PIN = 13;
Servo lidServo;

const int LID_CLOSED = 0;
const int LID_OPEN = 90;

// -------- L298N motor driver --------
const int ENA = 25;
const int IN1 = 26;
const int IN2 = 27;

const int ENB = 14;
const int IN3 = 18;
const int IN4 = 19;

// -------- Robot settings --------
const float DETECT_DISTANCE = 15.0;

// Calibrate this value so the robot travels about 1 meter.
const unsigned long RUN_TIME = 1000;

const int MOTOR_SPEED = 180;  // 0 to 255

// Read object distance in centimetres
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 25000);

  if (duration == 0) {
    return 999.0;  // No valid echo
  }

  return duration * 0.0343 / 2.0;
}

// Stop all motors
void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Move forward
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

// Move backward
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

// Stop, open lid, wait, close lid
void collectWaste() {
  stopMotors();
  delay(300);

  Serial.println("Object detected!");
  Serial.println("Waste collection started");

  lidServo.write(LID_OPEN);
  delay(2000);  // Allow waste to enter the bin

  lidServo.write(LID_CLOSED);
  delay(700);

  Serial.println("Lid closed");
  Serial.println("Run resumed");
}

// Move forward about 1 meter while checking for objects.
// Travel time counts only while moving.
void moveForwardRun() {
  unsigned long travelled = 0;

  while (travelled < RUN_TIME) {
    float distance = getDistance();

    if (distance <= DETECT_DISTANCE) {
      collectWaste();
      travelled += 40;  // Prevents repeating forever on the same object
    } else {
      forward();
      delay(40);
      stopMotors();
      travelled += 40;
    }
  }

  stopMotors();
  delay(300);
}

// Move backward to the starting point
void moveBackwardRun() {
  unsigned long travelled = 0;

  while (travelled < RUN_TIME) {
    backward();
    delay(40);
    stopMotors();
    travelled += 40;
  }

  stopMotors();
  delay(300);
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  lidServo.setPeriodHertz(50);
  lidServo.attach(SERVO_PIN, 500, 2400);
  lidServo.write(LID_CLOSED);

  stopMotors();
  delay(1000);

  Serial.println("Autonomous Waste Collection Robot");
  Serial.println("System ready");
}

void loop() {
  moveForwardRun();   // Forward about 1 meter, collecting waste
  moveBackwardRun();  // Return to the starting point
}
