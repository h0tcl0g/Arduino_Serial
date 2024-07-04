#include <Servo.h>
#include <SR04.h>
#include "SR04.h"

#define ECHO_PIN 8
#define TRIG_PIN 9
#define PULSE_PIN 10
#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define DEFAULT_ANGLE 90
#define DISTANCE 40


SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
Servo myservo;

int pos = DEFAULT_ANGLE;
int dist = 0;
int returnAngle = 0;
int returnFlag = 0;
int centerAngle = DEFAULT_ANGLE;
int movSpeed = 1;


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
    switch (data) {
      case '1':
        movSpeed = 1;
        break;
      case '2':
        movSpeed = 2;
        break;
      case '3':
        movSpeed = 3;
        break;
      case '4':
        movSpeed = 4;
        break;
      case '5':
        movSpeed = 5;
        break;
      case '6':
        movSpeed = 6;
        break;
      case '7':
        movSpeed = 7;
        break;
      case '8':
        movSpeed = 8;
        break;
      case '9':
        movSpeed = 9;
        break;
      case '10':
        movSpeed = 10;
        break;
      default:
        break;
    }

    if (data == 'reset') {
      centerAngle = DEFAULT_ANGLE;
      pos = 90;
      delay(1000);
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
    if (dist < DISTANCE) {
      returnAngle = 0;
      centerAngle = pos;
      break;
    }
    
    if (returnFlag == 0) {
      pos += movSpeed;
      myservo.write(pos);
    } else if (returnFlag == 1) {
      pos -= movSpeed;
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
  returnAngle += 10;
}
