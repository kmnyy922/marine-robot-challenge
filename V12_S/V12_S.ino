#include <Servo.h>
Servo servo;

#include <DynamixelShield.h>
DynamixelShield dxl;

enum {
  L1 = 3,
  L2 = 5,
  R1 = 6,
  R2 = 11
};

int ec = A0;
int tr = A1;

int duration = 0;
int s = 90;

void setup() {
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(ec, INPUT);
  pinMode(tr, OUTPUT);
  Serial.begin(57600);
  dxl.rc100.begin();
  servo.write(90);
  servo.attach(9);
}

void loop() {
  int data;
  if (dxl.rc100.available() > 0) {
    data = dxl.rc100.readData();
    Serial.println(data);
    if (data == 1) {
      go();
    }
    if (data == 2) {
      back();
    }
    if (data == 4) {
      left();
    }
    if (data == 8) {
      right();
    }
    if (data == 16) {
      while (1) {
        if (getDistanceCM() < 46 && s == 90) {
          stopp();
          servo.write(180);
          s = 180;
          delay(500);
        }
        if (getDistanceCM() < 45 && s == 180) {
          servo.write(0);
          s = 0;
          delay(500);
        }
        if (getDistanceCM() < 45 && s == 0) {
          servo.write(90);
          s = 90;
          delay(500);
          back();
          delay(3000);
          go();
          delay(2000);
        }
        if (s == 180 || s == 0) {
          stopp();
        }
        else {
          go();
        }
      }
    }
    else
    {
      stopp();
    }
  }
}
void back()
{
  analogWrite(R1, 0);
  analogWrite(R2, 62);
  analogWrite(L1, 60);
  analogWrite(L2, 0);
  delay(50);
}
void go()
{
  analogWrite(R1, 62);
  analogWrite(R2, 0);
  analogWrite(L1, 0);
  analogWrite(L2, 60);
  delay(50);
}
void right()
{
  analogWrite(R1, 62);
  analogWrite(R2, 0);
  analogWrite(L1, 60);
  analogWrite(L2, 0);
  delay(50);
}
void left()
{
  analogWrite(R1, 0);
  analogWrite(R2, 62);
  analogWrite(L1, 0);
  analogWrite(L2, 60);
  delay(50);
}
void stopp()
{
  analogWrite(R1, 0);
  analogWrite(R2, 0);
  analogWrite(L1, 0);
  analogWrite(L2, 0);
}
float getDistanceCM() {
  long  duration, distance;
  digitalWrite(tr, LOW);
  delayMicroseconds(2);
  digitalWrite(tr, HIGH);
  delayMicroseconds(10);
  digitalWrite(tr, LOW);
  duration = pulseIn(ec, HIGH);  // pulseIn 거리값명령어
  distance = duration * 17 / 1000;
  Serial.println(distance);
  delay(100);
  return distance;
}
