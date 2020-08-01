// Ved P. Sharma, May 5, 2013, version 03
// Robot follows black line, turns 180 deg and comes back
// and follows the same line back

#include <QTRSensors.h>
#define NUM_SENSORS   2
#define TIMEOUT       2500
#define EMITTER_PIN   QTR_NO_EMITTER_PIN

QTRSensorsRC qtrrc((unsigned char[]) {3, 4}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensors[NUM_SENSORS];

const int m1Pin1 = 5;  const int m1Pin2 = 6;
const int m2Pin1 = 7;  const int m2Pin2 = 8;
const int m1enablePin = 9;  const int m2enablePin = 10;
int a = 0, b = 0, i=0;
int wheelSpeed = 255, turnSpeed = 100, lower = 800, upper = 1400;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  pinMode(m1Pin1, OUTPUT);  pinMode(m1Pin2, OUTPUT); 
  pinMode(m2Pin1, OUTPUT);  pinMode(m2Pin2, OUTPUT); 
  pinMode(m1enablePin, OUTPUT);  pinMode(m2enablePin, OUTPUT);
  do {
    delay(250);
    qtrrc.read(sensors);  a = sensors[0];  b = sensors[1];
    Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
  } while ((a<lower || a>upper) || (b<lower || b>upper));

  digitalWrite(13, HIGH); delay(2000);digitalWrite(13, LOW); // LED indicates that both the sensors are on black line
  analogWrite(m1enablePin, wheelSpeed);  analogWrite(m2enablePin, wheelSpeed); 
  digitalWrite(m1Pin1, HIGH); digitalWrite(m1Pin2, LOW);
  digitalWrite(m2Pin1, HIGH); digitalWrite(m2Pin2, LOW);
}

void loop() {
  for(i=0;i<300;i++){
    check();
    delay(20);
  }
  turn();
  for(i=0;i<300;i++){
    check();
    delay(20);
  }
  turn();
//  analogWrite(m1enablePin, 0);  analogWrite(m2enablePin, 0); 
//  delay(1000);
//  analogWrite(m1enablePin, wheelSpeed);  analogWrite(m2enablePin, wheelSpeed); 
}

void check() {
  qtrrc.read(sensors);  a = sensors[0];  b = sensors[1];
  Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
  if(a<lower && b>lower && b<upper){
    do {
      analogWrite (m2enablePin, 0);
      qtrrc.read(sensors);a = sensors[0];  b = sensors[1];
      Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
    }
    while (a<lower);
    analogWrite (m2enablePin, wheelSpeed);
  }
  else if (b<lower && a>lower && a<upper){
    do {
      analogWrite (m1enablePin, 0);
      qtrrc.read(sensors);a = sensors[0];  b = sensors[1];
      Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
    }
    while (b<lower);
    analogWrite (m1enablePin, wheelSpeed);
  }
}

void turn(){
  analogWrite(m1enablePin, turnSpeed);  analogWrite(m2enablePin, turnSpeed); 
  digitalWrite(m1Pin1, LOW); digitalWrite(m1Pin2, HIGH);
  delay(300); // this delay imp for robot to move out of the line
  do {
    qtrrc.read(sensors);a = sensors[0];  b = sensors[1];
    Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
  }
  while (a<lower || b<lower);
  digitalWrite(m1Pin1, HIGH); digitalWrite(m1Pin2, LOW); 
  analogWrite(m1enablePin, wheelSpeed);  analogWrite(m2enablePin, wheelSpeed); 
}

