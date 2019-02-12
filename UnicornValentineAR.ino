#include <Servo.h>

const int SERVO_PIN = 2;
const int MOVE_DELAY = 20;
const int MAX_DEGREE = 90; 

const int JOY_X_PIN = 0;
const int JOY_Y_PIN = 1;
const int JOY_BUTTON_PIN = 3;

Servo servo;
int current_position = 90;
const int MOVE_DELTA = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);

  pinMode(JOY_BUTTON_PIN, INPUT);
  digitalWrite(JOY_BUTTON_PIN, LOW);
}

void loop() {
  //scan();
 int y_pos = analogRead(JOY_Y_PIN);
 // right
 if (y_pos < 300 && current_position > 10) {
  current_position -= MOVE_DELTA;
 } else if (y_pos > 800 && current_position < 180 ) {
  current_position += MOVE_DELTA;
 }
 servo.write(current_position);
 Serial.print("Pos: ");
 Serial.print(current_position);
 Serial.print(" | Y: ");
 Serial.println(y_pos);
 delay(MOVE_DELAY);
}


void debugJoystick() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(JOY_BUTTON_PIN));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(JOY_X_PIN));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(JOY_Y_PIN));
  Serial.print("\n\n");
  delay(500);
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
