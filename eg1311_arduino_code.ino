#include <Servo.h>
Servo servo;

//Below are the variables and pins used
int MOTOR_1A = 4;
int MOTOR_1B = 5;
int MOTOR_2A = 6;
int MOTOR_2B = 7;
int TRIG = 13;
int ECHO = 12;
int servo_pin = 3;
bool stopped_once = false;
float sound_speed = 0.0345;

//Function below moves the robot forward
void forward()
{
  digitalWrite(MOTOR_1A, HIGH);
  digitalWrite(MOTOR_1B, LOW);
  digitalWrite(MOTOR_2A, HIGH);
  digitalWrite(MOTOR_2B, LOW);
}

//Function below stops the vehicle
void stop()
{
  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_1B, LOW);
  digitalWrite(MOTOR_2A, LOW);
  digitalWrite(MOTOR_2B, LOW);
}

//Function below moves the robot backwards
void backward()
{
  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_1B, HIGH);
  digitalWrite(MOTOR_2A, LOW);
  digitalWrite(MOTOR_2B, HIGH);
}

// Below this section are the main codes
void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(MOTOR_2A, OUTPUT);
  pinMode(MOTOR_2B, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
  servo.attach(servo_pin,300,2700);
  servo.write(180);
}

void loop()
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  int time_of_pulse = pulseIn(ECHO, HIGH);
  float distance = (time_of_pulse * sound_speed) / 2;
  Serial.println(distance);
  if ((distance < 11) && !(stopped_once)){
    stop();
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(180);
    stopped_once = true;
  }
  else if (stopped_once) {
    backward();
  }
  else {
    forward();
  }
  delay(10);
}