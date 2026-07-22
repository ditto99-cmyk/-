#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(6);
}

void loop() {
  myservo.write(90);
}
