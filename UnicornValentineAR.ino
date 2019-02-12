#include <Servo.h>

const int SERVO_PIN = 2;
const int MOVE_DELAY = 20;
const int MAX_DEGREE = 90; 

Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
}

void loop() {
  //scan();
}

void scan() {
  for (int i=0; i<MAX_DEGREE; i++) {
    servo.write(i);
    delay(MOVE_DELAY);
    Serial.println("Set position to: " + String(i));
  }
  for (int i=MAX_DEGREE; i >= 0; --i) {
    servo.write(i);
    delay(MOVE_DELAY);
  }
}
