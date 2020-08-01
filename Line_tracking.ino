// Ved P. Sharma, May 4, 2013, version 02
// This version is for two wheels (+DC motors) in the center with support
// at the front and back by two tmaiya caster wheels.
// Relectance sensros in the middle aligning with the wheels was not 
// not a good configuration. Had to move them at the front to get the
// triangle configuration with 2 wheels and reflectance sensors

#include <QTRSensors.h>
#define NUM_SENSORS   2
#define TIMEOUT       2500
#define EMITTER_PIN   QTR_NO_EMITTER_PIN

QTRSensorsRC qtrrc((unsigned char[]) {3, 4}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

const int m1Pin1 = 5;  const int m1Pin2 = 6;
const int m2Pin1 = 7;  const int m2Pin2 = 8;
const int m1enablePin = 9;  const int m2enablePin = 10;
int a = 0, b = 0;
int wheelSpeed = 255, turnSpeed = 150, lower = 800, upper = 1400;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  pinMode(m1Pin1, OUTPUT);  pinMode(m1Pin2, OUTPUT); 
  pinMode(m2Pin1, OUTPUT);  pinMode(m2Pin2, OUTPUT); 
  pinMode(m1enablePin, OUTPUT);  pinMode(m2enablePin, OUTPUT);
  do {
    delay(250);
    qtrrc.read(sensorValues);
    a = sensorValues[0];  b = sensorValues[1];
    Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
  } while ((a<lower || a>upper) || (b<lower || b>upper));

  digitalWrite(13, HIGH); delay(2000);digitalWrite(13, LOW); // LED indicates that both the sensors are on black line
  analogWrite(m1enablePin, wheelSpeed);  analogWrite(m2enablePin, wheelSpeed); 
  digitalWrite(m1Pin1, HIGH); digitalWrite(m1Pin2, LOW);
  digitalWrite(m2Pin1, HIGH); digitalWrite(m2Pin2, LOW);
}

void loop() {
  delay(100);
  qtrrc.read(sensorValues);
  a = sensorValues[0];  b = sensorValues[1];
  Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
  if(a<lower && b>lower && b<upper){
    do {
//      delay(10);
      analogWrite (m2enablePin, 0);
//      analogWrite (m1enablePin, turnSpeed);
      qtrrc.read(sensorValues);a = sensorValues[0];  b = sensorValues[1];
      Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
    }
    while (a<lower);
    analogWrite (m2enablePin, wheelSpeed);
  }
  else if (b<lower && a>lower && a<upper){
    do {
//      delay(10);
      analogWrite (m1enablePin, 0);
//      analogWrite (m2enablePin, turnSpeed);
      qtrrc.read(sensorValues);a = sensorValues[0];  b = sensorValues[1];
      Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
    }
    while (b<lower);
    analogWrite (m1enablePin, wheelSpeed);
  }
}
