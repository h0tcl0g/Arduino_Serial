#include <Servo.h>
#include <SR04.h>
#include "SR04.h"

#define ECHO_PIN 8
#define TRIG_PIN 9
#define PULSE_PIN 10
#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define DEFAULT_ANGLE 90


SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
Servo myservo;

int pos = DEFAULT_ANGLE;
int dist = 0;
int returnAngle = 0;
int returnFlag = 0;
int centerAngle = DEFAULT_ANGLE;


void setup() {
  myservo.attach(PULSE_PIN);
  Serial.begin(9600);
  delay(1000);
  myservo.write(pos);
}

void loop() {
  receiveSerial();
  moveServo();
}

void receiveSerial() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    if (data == '1') {
      returnAngle = 0;
      delay(1000);
    } else if (data == '0') {
      centerAngle = DEFAULT_ANGLE;
    }
  }
}

void moveServo() {
  while (true) {
    dist = sr04.Distance();
    Serial.print(dist);
    Serial.println("cm");
    Serial.println(centerAngle);
    Serial.println(returnFlag);
    if (dist < 50) {
      returnAngle = 0;
      centerAngle = pos;
      break;
    }
    
    if (returnFlag == 0) {
      pos += 1;
      myservo.write(pos);
    } else if (returnFlag == 1) {
      pos -= 1;
      myservo.write(pos);
    }

    if (centerAngle + returnAngle <= pos || pos > MAX_ANGLE) {
      returnFlag = 1;
      break;
    } else if (centerAngle - returnAngle >= pos || pos < MIN_ANGLE) {
      returnFlag = 0;
      break;
    }

  }
  returnAngle += 1;
}
