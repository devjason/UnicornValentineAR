#include <Servo.h>

const int SERVO_PIN = 2;
const int MOVE_DELAY = 20;
const int MAX_DEGREE = 90; 

const int JOY_X_PIN = 0;
const int JOY_Y_PIN = 1;
const int JOY_BUTTON_PIN = 3;

const int LED_L_PIN = 7;
const int LED_R_PIN = 6;
int ledCount = 0;
bool ledMode = true;

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

   pinMode(LED_L_PIN, OUTPUT);
   pinMode(LED_R_PIN, OUTPUT);
}

void loop() {
  bool moved = handleMovement();
  handleLEDs(moved);
  delay(MOVE_DELAY);
}

void handleLEDs(bool moved) {
  if (ledCount++ == 5) {
    ledCount = 0;
    ledMode = !ledMode;
  }
  
  digitalWrite(LED_L_PIN, HIGH);
  digitalWrite(LED_R_PIN, HIGH);
  if (moved && !ledMode) {
    digitalWrite(LED_L_PIN, LOW);
    digitalWrite(LED_R_PIN, LOW);
  }
}

bool handleMovement() {
  bool moved = false;
  int y_pos = analogRead(JOY_Y_PIN);
  // right
  if (y_pos < 300 && current_position > 10) {
    current_position -= MOVE_DELTA;
    moved = true;
  } else if (y_pos > 800 && current_position < 180 ) {
  current_position += MOVE_DELTA;
  moved = true;
  }
  if (moved) {
    servo.write(current_position);
    Serial.print("Pos: ");
    Serial.print(current_position);
    Serial.print(" | Y: ");
    Serial.println(y_pos);
  }
  return moved;
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
