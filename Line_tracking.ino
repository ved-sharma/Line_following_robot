// Ved P. Sharma, May 2, 2013, version 1
// This version works good with two wheels (+DC motors) at the back and
// two tmaiya caster wheels at the front. Robot does not wobbel much
// while trying to turn to keep itself on the line.

#include <QTRSensors.h>

#define NUM_SENSORS   2
#define TIMEOUT       2500
#define EMITTER_PIN   QTR_NO_EMITTER_PIN

QTRSensorsRC qtrrc((unsigned char[]) {3, 4}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

const int m1Pin1 = 5;  const int m1Pin2 = 6;
const int m2Pin1 = 7;  const int m2Pin2 = 8;
const int m1enablePin = 9;  const int m2enablePin = 10;
int a = 0;  int b = 0;
  
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
  } while ((a<700 || a>1500) || (b<700 || b>1500));
  digitalWrite(13, HIGH); delay(2000);digitalWrite(13, LOW); // LED indicates that both the sensors are on black line
  
  digitalWrite(m1enablePin, 150);  digitalWrite(m2enablePin, 150); 
  digitalWrite(m1Pin1, HIGH); digitalWrite(m1Pin2, LOW);
  digitalWrite(m2Pin1, HIGH); digitalWrite(m2Pin2, LOW);
}

void loop() {
  delay(10);
  qtrrc.read(sensorValues);
  a = sensorValues[0];  b = sensorValues[1];
  Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
  if((a<700 || a>1500) && b>700 && b<1500){
    do {
//      delay(500);
      analogWrite (m2enablePin, 0); analogWrite (m1enablePin, 150);
      qtrrc.read(sensorValues);a = sensorValues[0];  b = sensorValues[1];
      Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
    }
    while (a<700 || a>1500);
  }
  else if ((b<700 || b>1500) && a>700 && a<1500){
    do {
//      delay(500);
      analogWrite (m1enablePin, 0); analogWrite (m2enablePin, 150);
      qtrrc.read(sensorValues);a = sensorValues[0];  b = sensorValues[1];
      Serial.print(a);  Serial.print('\t');  Serial.print(b);  Serial.println();
    }
    while (b<700 || b>1500);
  }
  analogWrite (m1enablePin, 150); analogWrite (m2enablePin, 150);
}
