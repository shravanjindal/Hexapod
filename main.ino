
//                   
//    |      .. (Angle theta)
//    | A  .    .        
//    |  .        .   B    
//  > |.____________.___________________
//  | |(Angle phi)    .
//  z |                 .
//  | |                   .
//  | |                     .
//  >  <-------- y --------->
//  Third axis is X

// femur length = A = 4.75 cm
// leg length = B = 8.5 cm 

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> // PCA9685 Driver - 16 channel Servo Driver
#include <Servo.h> //
#include <math.h>

#include "functions.h"

struct leg{
  Adafruit_PWMServoDriver servo1 = Adafruit_PWMServoDriver(); // lower leg servo
  double theta; // calibration constant
  Adafruit_PWMServoDriver servo2 = Adafruit_PWMServoDriver();  // femur leg servo
  double phi;   // calibration constant
  Adafruit_PWMServoDriver servo3 = Adafruit_PWMServoDriver();  // joint servo
  double omega; // calibration constant
};

struct leg_6th{
  Servo servo1;
  double theta;
  Servo servo2;
  double phi;
  Servo servo3;
  double omega;
};

double x,y,z;
leg legs[5];
leg_6th leg5;
// leg[0] denote first leg
// leg[1] denote second leg
// ...
// leg[4] denote fifth leg
// leg5 denote sixth leg

void setup() {
  
  // calibration constants
  legs[0].theta = -50;
  legs[0].phi = 135;
  legs[0].omega = 0;
  legs[1].theta = 190;
  legs[1].phi = 83;
  legs[1].omega = 0;
  legs[2].theta = 190;
  legs[2].phi = 130;
  legs[2].omega = 0;
  legs[3].theta = 195;
  legs[3].phi = 90;
  legs[3].omega = 0;
  legs[4].theta = 0;   
  legs[4].phi = 0;    
  legs[4].omega = 0;
  leg5.theta = 83; 
  leg5.phi = 195;
  leg5.omega = 0;  

  // 18 pwm pins
  for(int i=0; i<5;i++){
    legs[i].servo1.begin();
    legs[i].servo2.begin();
    legs[i].servo3.begin();
    legs[i].servo1.setOscillatorFrequency(27000000);
    legs[i].servo2.setOscillatorFrequency(27000000);
    legs[i].servo3.setOscillatorFrequency(27000000);
    legs[i].servo1.setPWMFreq(50);
    legs[i].servo2.setPWMFreq(50);
    legs[i].servo3.setPWMFreq(50);
    delay(10);
  }
  leg5.servo1.attach(9);
  leg5.servo2.attach(10);
  leg5.servo3.attach(11);
  
  rest_position(4.75,8.5);
  Serial.begin(115200);
}


void loop() {
  // you can perform any function from the header file
}
















