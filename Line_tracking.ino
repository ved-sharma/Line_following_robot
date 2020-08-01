// Ved P. Sharma, May 25, 2013, version 04
// Line following with 3 sensors, Robot follows black line, stops at 
// the end, turns 180 deg and follows the same line back again

#include <QTRSensors.h>
#define NUM_SENSORS   3
#define TIMEOUT       2500
#define EMITTER_PIN   QTR_NO_EMITTER_PIN

QTRSensorsRC qtrrc((unsigned char[]) {2, 3, 4}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensors[NUM_SENSORS];

const int m1Pin1 = 5;  const int m1Pin2 = 6;
const int m2Pin1 = 7;  const int m2Pin2 = 8;
const int m1enablePin = 0;  const int m2enablePin = 1;
unsigned int a=0, b=0, c=0, i=0;
//unsigned int minSen0=440, minSen1=768, minSen2=816, maxSen0=880, maxSen1=1676, maxSen2=1804;
unsigned int minSen0=360, minSen1=652, minSen2=712, maxSen0=832, maxSen1=1704, maxSen2=1816;
unsigned int wheelSpeed = 150, turnSpeed = 150, lower = 300, upper = 800;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  pinMode(m1Pin1, OUTPUT);  pinMode(m1Pin2, OUTPUT); 
  pinMode(m2Pin1, OUTPUT);  pinMode(m2Pin2, OUTPUT); 
  pinMode(m1enablePin, OUTPUT);  pinMode(m2enablePin, OUTPUT);
  do {
    delay(250);
    readSensors();
   } while (b<upper);

  digitalWrite(13, HIGH); delay(2000);digitalWrite(13, LOW); // LED indicates that both the sensors are on black line
  analogWrite(m1enablePin, wheelSpeed);  analogWrite(m2enablePin, wheelSpeed); 
  digitalWrite(m1Pin1, HIGH); digitalWrite(m1Pin2, LOW);
  digitalWrite(m2Pin1, HIGH); digitalWrite(m2Pin2, LOW);
}

void loop() {
  for(i=0;i<200;i++){
    check();
    delay(20);
  }
//  turn();
  for(i=0;i<200;i++){
    check();
    delay(20);
  }
//  turn();
//  analogWrite(m1enablePin, 0);  analogWrite(m2enablePin, 0); 
//  delay(1000);
//  analogWrite(m1enablePin, wheelSpeed);  analogWrite(m2enablePin, wheelSpeed); 
}

void readSensors() {
  delay(10);
  qtrrc.read(sensors);
  if(sensors[0]<minSen0)  sensors[0]=minSen0;
  if(sensors[0]>maxSen0)  sensors[0]=maxSen0;
  if(sensors[1]<minSen1)  sensors[1]=minSen1;
  if(sensors[1]>maxSen1)  sensors[1]=maxSen1;
  if(sensors[2]<minSen2)  sensors[2]=minSen2;
  if(sensors[2]>maxSen2)  sensors[2]=maxSen2;
  a = (((unsigned long)sensors[0])-minSen0) * 1000 / (maxSen0-minSen0);
  b = (((unsigned long)sensors[1])-minSen1) * 1000 / (maxSen1-minSen1);
  c = (((unsigned long)sensors[2])-minSen2) * 1000 / (maxSen2-minSen2);
  Serial.print(a);Serial.print('\t');  Serial.print(b);Serial.print('\t');  Serial.print(c);Serial.println();
}

void check() {
  readSensors();
  if(b<upper && c>a){
    do {
      analogWrite (m2enablePin, 0);
      readSensors();
    }
    while (b<upper);
    analogWrite (m2enablePin, wheelSpeed);
  }
  else if (b<upper && a>c){
    do {
      analogWrite (m1enablePin, 0);
      readSensors();
    }
    while (b<upper);
    analogWrite (m1enablePin, wheelSpeed);
  }
//
  else if (b>upper && a>upper && c>upper){
    analogWrite (m1enablePin, 0);
    analogWrite (m2enablePin, 0);
    delay(3000);
    turn();
  }
//
}

void turn(){
  analogWrite(m1enablePin, turnSpeed);  analogWrite(m2enablePin, turnSpeed); 
  digitalWrite(m1Pin1, LOW); digitalWrite(m1Pin2, HIGH);
  delay(1000); // this delay imp for robot to move out of the line
  do {
    delay(10);
    readSensors();
  }
  while (a<upper && b<upper && c<upper); // while any one of the sensors comes on the line
  digitalWrite(m1Pin1, HIGH); digitalWrite(m1Pin2, LOW); 
  analogWrite(m1enablePin, wheelSpeed);  analogWrite(m2enablePin, wheelSpeed); 
}

