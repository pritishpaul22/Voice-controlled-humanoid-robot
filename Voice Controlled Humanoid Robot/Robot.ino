#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

#include <Arduino.h>
#include "Hash_V2.h"

Hash_V2 robot;

void setup() {
  Serial.begin(9600);
  robot.init_hash();
  robot.initial_position();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    int steps, speed;
    switch(command) {
      case 'f':
        Serial.println("Enter number of steps and speed:");
        while(Serial.available() < 4);
        steps = Serial.parseInt();
        speed = Serial.parseInt();
        robot.forward(steps, speed);
        break;
      case 'b':
        Serial.println("Enter number of steps and speed:");
        while(Serial.available() < 4);
        steps = Serial.parseInt();
        speed = Serial.parseInt();
        robot.backward(steps, speed);
        break;
      case 'l':
        Serial.println("Enter number of steps and speed:");
        while(Serial.available() < 4);
        steps = Serial.parseInt();
        speed = Serial.parseInt();
        robot.turn_left(steps, speed);
        break;
      case 'r':
        Serial.println("Enter number of steps and speed:");
        while(Serial.available() < 4);
        steps = Serial.parseInt();
        speed = Serial.parseInt();
        robot.turn_right(steps, speed);
        break;
      case 's':
        Serial.println("Enter speed:");
        while(Serial.available() < 2);
        speed = Serial.parseInt();
        robot.stop(speed);
        break;
      case 'p':
        Serial.println("Enter speed:");
        while(Serial.available() < 2);
        speed = Serial.parseInt();
        robot.pick_up(speed);
        break;
      case 'h':
        Serial.println("Enter count and speed:");
        while(Serial.available() < 4);
        int count = Serial.parseInt();
        speed = Serial.parseInt();
        robot.say_hi(count, speed);
        break;
      default:
        Serial.println("Invalid command!");
    }
  }
}
Servo servo[20] = {};

#include "Hash_V2.h"

/* Initializing servo drive and OLED display */
void Hash_V2::init_hash() {

  int servo_pins[20] = {2, 3, 4, 5, 6, 7, 8, 9, 52, 53, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};

  for (int i = 0; i < 20; i++) {
    servo[i].attach(servo_pins[i]);
  }

}

/* Initial position */
void Hash_V2::initial_position() {
  int degree_array[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  for (int i = 0; i < 20; i++) {
    servo_position[i] = degree_array[i];
  }
  move_servo(2000, degree_array);
}
/* Moving each servo at given time interval */
void Hash_V2::move_servo(int time, int  servo_target[]) {

  if (time > 10) {
    for (int i = 0; i < 20; i++) {
      increment[i] = ((servo_target[i]) - servo_position[i]) / (time / 10.0);
    }
    final_time =  millis() + time;

    for (int iteration = 1; millis() < final_time; iteration++) {
      partial_time = millis() + 10;

      for (int i = 0; i < 20; i++) {
        servo[i].write((int)(servo_position[i] + (iteration * increment[i])));
      }
      while (millis() < partial_time);
    }
  }
  else {
    for (int i = 0; i < 20; i++) {
      servo[i].write((int)servo_target[i]);
    }
  }
  for (int i = 0; i < 20; i++) {
    servo_position[i] = servo_target[i];
  }
}


/**********************************/

void Hash_V2::say_hi(int count, int speed) {

  int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 180, 90, 90, 150, 150, 150, 90, 90};
  move_servo(speed * 2, degree_array1);
  for (int i = 1; i <= count; i++) {
    int degree_array2[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 180, 90, 60, 150, 150, 150, 90, 90};
    int degree_array3[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 180, 90, 120, 150, 150, 150, 90, 90};
    move_servo(speed, degree_array2);
    move_servo(speed, degree_array3);
  }
  int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 180, 90, 90, 150, 150, 150, 90, 90};
  int degree_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array4);
  move_servo(speed * 2, degree_array5);
}

/**********************************/

void Hash_V2::forward(int steps, int speed) {
  if (speed < 500) {
    speed = 500;
  }
  int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  int degree_array2[20] = {110, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  int degree_array3[20] = {110, 150, 120, 60, 110, 90, 105, 30, 30, 150, 90, 90, 20, 30, 30, 120, 150, 150, 90, 90};
  int degree_array4[20] = {90, 150, 120, 60, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array1);
  move_servo(speed, degree_array2);
  move_servo(speed, degree_array3);
  move_servo(speed, degree_array4);
  for (int i = 1; i <= steps; i++) {
    int degree_array5[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int degree_array6[20] = {70, 150, 150, 30, 90, 90, 70, 30, 60, 120, 70, 90, 60, 30, 30, 160, 150, 150, 90, 90};
    int degree_array7[20] = {90, 150, 150, 30, 90, 90, 90, 30, 60, 120, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int degree_array8[20] = {110, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int degree_array9[20] = {110, 150, 120, 60, 110, 90, 105, 30, 30, 150, 90, 90, 20, 30, 30, 120, 150, 150, 90, 90};
    int degree_array10[20] = {90, 150, 120, 60, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, degree_array5);
    move_servo(speed, degree_array6);
    move_servo(speed, degree_array7);
    move_servo(speed, degree_array8);
    move_servo(speed, degree_array9);
    move_servo(speed, degree_array10);
  }
  int degree_array11[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array11);
}

/**************************************/

void Hash_V2::turn_right(int steps, int speed) {
  if (speed < 500) {
    speed = 500;
  }
  int pwm_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array1);
  for (int i = 1; i <= steps; i++) {
    int pwm_array2[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array3[20] = {70, 150, 145, 30, 90, 80, 70, 30, 30, 150, 70, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array4[20] = {90, 150, 145, 30, 90, 80, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array5[20] = {110, 150, 150, 30, 110, 80, 105, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array6[20] = {110, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array7[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, pwm_array2);
    move_servo(speed, pwm_array3);
    move_servo(speed, pwm_array4);
    move_servo(speed, pwm_array5);
    move_servo(speed, pwm_array6);
    move_servo(speed, pwm_array7);
  }
  int pwm_array8[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array8);
}

/**********************************/

void Hash_V2::turn_left(int steps, int speed) {
  if (speed < 500) {
    speed = 500;
  }
  int pwm_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array1);
  for (int i = 1; i <= steps; i++) {
    int pwm_array2[20] = {110, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array3[20] = {110, 150, 150, 30, 110, 90, 105, 30, 35, 150, 90, 100, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 35, 150, 90, 100, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array5[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 100, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array6[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    int pwm_array7[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, pwm_array2);
    move_servo(speed, pwm_array3);
    move_servo(speed, pwm_array4);
    move_servo(speed, pwm_array5);
    move_servo(speed, pwm_array6);
    move_servo(speed, pwm_array7);
  }
  int pwm_array8[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array8);
}

/**********************************/

void Hash_V2::move_right(int steps, int speed) {
  int pwm_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array1);
  for (int i = 1; i <= steps; i++) {
    int pwm_array2[20] = {110, 150, 150, 30, 112, 90, 90, 30, 30, 150, 90, 90, 30, 60, 30, 120, 150, 150, 90, 90};
    int pwm_array3[20] = {70, 150, 150, 30, 70, 90, 70, 30, 30, 150, 70, 90, 30, 60, 30, 120, 150, 150, 90, 90};
    int pwm_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, pwm_array2);
    move_servo(speed, pwm_array3);
    move_servo(speed, pwm_array4);
  }
  int pwm_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array5);
}

/**********************************/

void Hash_V2::move_left(int steps, int speed) {
  int pwm_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array1);
  for (int i = 1; i <= steps; i++) {
    int pwm_array2[20] = {90, 150, 150, 30, 90, 90, 70, 30, 30, 150, 68, 90, 50, 30, 30, 150, 120, 150, 90, 90};
    int pwm_array3[20] = {110, 150, 150, 30, 110, 90, 110, 30, 30, 150, 110, 90, 50, 30, 30, 150, 120, 150, 90, 90};
    int pwm_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, pwm_array2);
    move_servo(speed, pwm_array3);
    move_servo(speed, pwm_array4);
  }
  int pwm_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array5);
}

/**********************************/

void Hash_V2::ball_kick_right(int count, int speed) {
  int pwm_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array1);
  for (int i = 1; i <= count; i++) {
    int pwm_array2[20] = {112, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90, 90, 10, 30, 30, 90, 150, 150, 90, 90};
    int pwm_array3[20] = {112, 130, 140, 10, 110, 90, 105, 30, 30, 150, 90, 90, 10, 30, 30, 90, 150, 150, 90, 90};
    int pwm_array4[20] = {112, 150, 140, 60, 110, 90, 105, 30, 30, 150, 90, 90, 10, 30, 30, 90, 150, 150, 90, 90};
    int pwm_array5[20] = {112, 150, 150, 30, 110, 90, 105, 30, 30, 150, 90, 90, 10, 30, 30, 90, 150, 150, 90, 90};
    move_servo(speed, pwm_array2);
    move_servo(speed / 2, pwm_array3);
    move_servo(speed / 2, pwm_array4);
    move_servo(speed, pwm_array5);
  }
  int pwm_array6[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array6);
}

/**********************************/

void Hash_V2::ball_kick_left(int count, int speed) {
  int pwm_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array1);
  for (int i = 1; i <= count; i++) {
    int pwm_array2[20] = {70, 150, 150, 30, 90, 90, 68, 30, 30, 150, 70, 90, 90, 30, 30, 170, 150, 150, 90, 90};
    int pwm_array3[20] = {70, 150, 150, 30, 90, 90, 68, 50, 40, 170, 70, 90, 90, 30, 30, 170, 150, 150, 90, 90};
    int pwm_array4[20] = {70, 150, 150, 30, 90, 90, 68, 30, 40, 120, 70, 90, 90, 30, 30, 170, 150, 150, 90, 90};
    int pwm_array5[20] = {70, 150, 150, 30, 90, 90, 68, 30, 30, 150, 70, 90, 90, 30, 30, 170, 150, 150, 90, 90};
    move_servo(speed, pwm_array2);
    move_servo(speed / 2, pwm_array3);
    move_servo(speed / 2, pwm_array4);
    move_servo(speed, pwm_array5);
  }
  int pwm_array6[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array6);
}

/**********************************/

void Hash_V2::max_sit(int count, int speed) {
  for (int i = 1; i <= count; i++) {
    int degree_array1[20] = {90, 70, 60, 30, 90, 90, 90, 110, 120, 150, 90, 90, 30, 60, 30, 150, 120, 150, 90, 90};
    int degree_array2[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, degree_array1);
    delay(3000);
    move_servo(speed, degree_array2);
  }
}

/**********************************/

void Hash_V2::bow(int count, int speed) {
  for (int i = 1; i <= count; i++) {
    int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 50, 50, 30, 130, 130, 150, 90, 90};
    int degree_array2[20] = {90, 160, 150, 60, 90, 90, 90, 20, 30, 120, 90, 90, 50, 50, 30, 130, 130, 150, 90, 90};
    int degree_array3[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 50, 50, 30, 130, 130, 150, 90, 90};
    move_servo(speed / 2, degree_array1);
    move_servo(speed, degree_array2);
    delay(3000);
    move_servo(speed, degree_array3);
  }
  int pwm_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, pwm_array4);
}

/**********************************/

/**********************************/

void Hash_V2::right_bow(int count, int speed) {
  for (int i = 1; i <= count; i++) {
    int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 90, 30, 30, 180, 150, 150, 90, 90};
    int degree_array2[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 90, 30, 90, 180, 150, 120, 90, 90};
    int degree_array3[20] = {90, 160, 150, 60, 90, 90, 90, 20, 30, 120, 90, 90, 90, 30, 90, 180, 150, 120, 90, 90};
    int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 90, 30, 90, 180, 150, 120, 90, 90};
    int degree_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 90, 30, 30, 180, 150, 150, 90, 90};
    move_servo(speed, degree_array1);
    move_servo(speed, degree_array2);
    move_servo(speed, degree_array3);
    delay(2000);
    move_servo(speed, degree_array4);
    move_servo(speed, degree_array5);
  }
  int degree_array6[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array6);
}

/**********************************/

void Hash_V2::left_bow(int count, int speed) {
  for (int i = 1; i <= count; i++) {
    int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 0, 30, 30, 90, 150, 150, 90, 90};
    int degree_array2[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 0, 30, 60, 90, 150, 90, 90, 90};
    int degree_array3[20] = {90, 160, 150, 60, 90, 90, 90, 20, 30, 120, 90, 90, 0, 30, 60, 90, 150, 90, 90, 90};
    int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 0, 30, 60, 90, 150, 90, 90, 90};
    int degree_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 0, 30, 30, 90, 150, 150, 90, 90};
    move_servo(speed, degree_array1);
    move_servo(speed, degree_array2);
    move_servo(speed, degree_array3);
    delay(2000);
    move_servo(speed, degree_array4);
    move_servo(speed, degree_array5);
  }
  int degree_array6[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array6);
}

/**********************************/

void Hash_V2::ape_move(int count, int speed) {
  int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 120, 60, 60, 60, 120, 120, 90, 90};
  int degree_array2[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 120, 60, 120, 60, 120, 120, 90, 90};
  move_servo(speed, degree_array1);
  move_servo(speed, degree_array2);
  for (int i = 1; i <= count; i++) {
    int degree_array3[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 120, 60, 60, 60, 120, 60, 120, 90};
    int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 120, 60, 120, 60, 120, 120, 60, 90};
    move_servo(speed / 2, degree_array3);
    move_servo(speed / 2, degree_array4);
  }
  int degree_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 120, 60, 60, 60, 120, 120, 90, 90};
  int degree_array6[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array5);
  move_servo(speed, degree_array6);
}

/**********************************/

void Hash_V2::push_up(int count, int speed) {
  int degree_array1[20] = {90, 70, 60, 30, 90, 90, 90, 110, 120, 150, 90, 90, 30, 60, 30, 150, 120, 150, 90, 90};
  int degree_array2[20] = {90, 70, 60, 30, 150, 90, 90, 110, 120, 150, 30, 90, 30, 60, 30, 150, 120, 150, 90, 90};
  int degree_array3[20] = {90, 70, 60, 30, 150, 90, 90, 110, 120, 150, 30, 90, 90, 30, 30, 90, 150, 150, 90, 90};
  int degree_array4[20] = {90, 70, 60, 0, 150, 90, 90, 110, 120, 180, 30, 90, 90, 30, 30, 90, 150, 150, 90, 90};
  int degree_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 100, 30, 30, 80, 150, 150, 90, 90};
  move_servo(speed, degree_array1);
  move_servo(speed, degree_array2);
  move_servo(speed, degree_array3);
  move_servo(speed, degree_array4);
  move_servo(speed, degree_array5);
  for (int i = 1; i <= count; i++) {
    int degree_array6[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 100, 90, 90, 80, 90, 90, 90, 90};
    int degree_array7[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 100, 30, 30, 80, 150, 150, 90, 90};
    move_servo(speed, degree_array6);
    move_servo(speed, degree_array7);
  }
  int degree_array8[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array8);
}

/**********************************/

void Hash_V2::clap(int count, int speed) {
  int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 180, 20, 30, 0, 160, 150, 90, 90};
  move_servo(speed, degree_array1);
  for (int i = 1; i <= count; i++) {
    int degree_array2[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 180, 20, 90, 0, 160, 90, 90, 90};
    int degree_array3[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 180, 20, 30, 0, 160, 150, 90, 90};
    move_servo(speed / 2, degree_array2);
    move_servo(speed / 2, degree_array3);
  }
  int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array4);
}

/**********************************/

void Hash_V2::right_leg_up(int count, int speed) {
  int degree_array1[20] = {110, 150, 150, 30, 110, 90, 110, 30, 30, 150, 90, 90, 30, 90, 30, 150, 90, 150, 90, 90};
  move_servo(speed, degree_array1);
  for (int i = 1; i <= count; i++) {
    int degree_array2[20] = {110, 150, 150, 30, 110, 90, 110, 30, 30, 150, 90, 90, 30, 150, 30, 150, 30, 150, 90, 90};
    int degree_array3[20] = {110, 150, 150, 30, 110, 90, 110, 30, 30, 150, 90, 90, 30, 90, 30, 150, 90, 150, 90, 90};
    move_servo(speed / 2, degree_array2);
    move_servo(speed / 2, degree_array3);
  }
  int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array4);
}

/**********************************/

void Hash_V2::left_leg_up(int count, int speed) {

  int degree_array1[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90, 30, 90, 30, 150, 90, 150, 90, 90};
  move_servo(speed, degree_array1);
  for (int i = 1; i <= count; i++) {
    int degree_array2[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90, 30, 150, 30, 150, 30, 150, 90, 90};
    int degree_array3[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90, 30, 90, 30, 150, 90, 150, 90, 90};
    move_servo(speed / 2, degree_array2);
    move_servo(speed / 2, degree_array3);
  }

  int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed, degree_array4);
}

/**********************************/

void Hash_V2::hip_pose(int count, int speed) {
  for (int i = 1; i <= count; i++) {
    int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 90, 120, 150, 90, 60, 90, 90};
    int degree_array2[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, degree_array1);
    delay(3000);
    move_servo(speed, degree_array2);
  }
}

/**********************************/

void Hash_V2::right_leg_balance(int count, int speed) {
  for (int i = 1; i <= count; i++) {
    int degree_array1[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90, 30, 90, 30, 150, 90, 150, 90, 90};
    int degree_array2[20] = {70, 150, 150, 30, 90, 90, 70, 110, 120, 150, 70, 90, 30, 90, 30, 150, 90, 150, 90, 90};
    int degree_array3[20] = {70, 150, 150, 30, 90, 90, 70, 30, 30, 150, 70, 90, 30, 90, 30, 150, 90, 150, 90, 90};
    int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, degree_array1);
    delay(3000);
    move_servo(speed, degree_array2);
    move_servo(speed, degree_array3);
    move_servo(speed, degree_array4);
  }
}

/**********************************/

void Hash_V2::left_leg_balance(int count, int speed) {
  for (int i = 1; i <= count; i++) {
    int degree_array1[20] = {110, 150, 150, 30, 110, 90, 110, 30, 30, 150, 90, 90, 30, 90, 30, 150, 90, 150, 90, 90};
    int degree_array2[20] = {90, 70, 60, 30, 110, 90, 110, 30, 30, 150, 90, 90, 30, 90, 30, 150, 90, 150, 90, 90};
    int degree_array3[20] = {110, 150, 150, 30, 110, 90, 110, 30, 30, 150, 90, 90, 30, 90, 30, 150, 90, 150, 90, 90};
    int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
    move_servo(speed, degree_array1);
    delay(3000);
    move_servo(speed, degree_array2);
    move_servo(speed, degree_array3);
    move_servo(speed, degree_array4);
  }
}

/**********************************/

void Hash_V2::flying_action(int count, int speed) {
  int degree_array1[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 120, 30, 150, 60, 150, 90, 90};
  move_servo(speed, degree_array1);
  for (int i = 1; i <= count; i++) {
    int degree_array2[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 150, 90, 150, 30, 90, 90, 90};
    int degree_array3[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 90, 0, 150, 90, 180, 90, 90};
    move_servo(speed / 2, degree_array2);
    move_servo(speed / 2, degree_array3);
  }
  int degree_array4[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 120, 30, 150, 60, 150, 90, 90};
  int degree_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed / 2 , degree_array4);
  move_servo(speed, degree_array5);
}

/**********************************/

void Hash_V2::hand_sit_zigzak(int count, int speed) {

  int degree_array1[20] = {90, 100, 95, 30, 90, 90, 90, 80, 85, 150, 90, 90, 30, 120, 120, 150, 60, 60, 90, 90};
  move_servo(speed, degree_array1);
  for (int i = 1; i <= count; i++) {
    int degree_array2[20] = {90, 100, 95, 30, 90, 90, 90, 80, 85, 150, 90, 90, 30, 120, 90, 150, 60, 30, 120, 90};
    int degree_array3[20] = {90, 100, 95, 30, 90, 90, 90, 80, 85, 150, 90, 90, 30, 120, 150, 150, 60, 90, 60, 90};
    move_servo(speed / 2, degree_array2);
    move_servo(speed / 2, degree_array3);
  }
  int degree_array4[20] = {90, 100, 95, 30, 90, 90, 90, 80, 85, 150, 90, 90, 30, 120, 120, 150, 60, 60, 90, 90};
  int degree_array5[20] = {90, 150, 150, 30, 90, 90, 90, 30, 30, 150, 90, 90, 30, 30, 30, 150, 150, 150, 90, 90};
  move_servo(speed / 2 , degree_array4);
  move_servo(speed, degree_array5);
}

/**********************************/
