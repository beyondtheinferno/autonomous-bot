//SERVO DECLARATIONS
#include<Servo.h>
const int servoPin = 13;     
Servo ultraBase;

//MOTOR DECLARATIONS
const int leftForward = 8; 
const int leftBackward = 9; 
const int rightForward = 11; 
const int rightBackward = 10;

//ULTRASONIC DECLARATIONS
const int echoPin = 7;
const int trigPin = 6;
long duration;
int distance;
int leftDistance, rightDistance;

#define COLLISION_DISTANCE 30
int d;

void setup() {
  Serial.begin(9600);
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ultraBase.attach(servoPin);
  ultraBase.write(90);                //Initial position of ultrasonic sensor - straight
}

void loop() {
  ultraBase.write(90);
  delay(100);
  d = readUltra();
  if(d <= COLLISION_DISTANCE)
  {
    stopMotion();
    Serial.print("Current Distance: ");
    Serial.println(d);
    changePath();
  }
  forward();
}

void forward() {
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);  
}

void left() {
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);
  delay(1000);                    //How long it should wait till it turns left - to be adjusted
}

void right() {
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , LOW);  
  delay(1000);                    //How long it should wait till it turns right - to be adjusted
}

void stopMotion() {
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , LOW);
}

int readUltra() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.println(distance);
  return distance;
}

void changePath() {
  ultraBase.write(180);       //Left
  delay(500);
  leftDistance = readUltra();
  Serial.print("Left Distance: ");
  Serial.println(leftDistance);
  delay(500);
  
  ultraBase.write(0);       //Right
  delay(500);
  rightDistance = readUltra();
  Serial.print("Right Distance: ");
  Serial.println(rightDistance);
  delay(500);
  
  if (leftDistance>rightDistance) 
    left();
  else
    right();
  ultraBase.write(90);
}

