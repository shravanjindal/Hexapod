
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


#include <math.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

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

double degrees_(double radians) {
  return radians * 180.0 / M_PI;
}
float map_(float value){
  return map(value,0,180,600,2400);
}
double theta(double y, double z){
  return degrees_(acos((94.8125 - ((y * y) + (z * z))) / 80.75));
}
double phi(double y, double z){
  return degrees_(acos(((y * y + z * z) - 49.6875) / (9.5 * (sqrt(y * y + z * z)))) - atan2(z, y));
}
void move_lower_leg(int leg_number, double y, double z){
  if(leg_number == 5){
    if(leg5.theta >= 90){
      leg5.servo1.write(leg5.theta - theta(y,z));
    }
    else{
      leg5.servo1.write(leg5.theta + theta(y,z));
    }
  }
  else{
    if(legs[leg_number].theta >= 90){
      legs[leg_number].servo1.writeMicroseconds(leg_number*3, map_(legs[leg_number].theta - theta(y,z)));;
    }
    else{
      legs[leg_number].servo1.writeMicroseconds(leg_number*3, map_(legs[leg_number].theta + theta(y,z)));;
    }
  }
}
void move_femur_leg(int leg_number, double y, double z){
  if(leg_number == 5){
    if(leg5.phi >= 90){
      leg5.servo1.write(leg5.phi - phi(y,z));
    }
    else{
      leg5.servo1.write(leg5.phi + phi(y,z));
    }
  }
  else{
    if(legs[leg_number].phi >= 90){
      legs[leg_number].servo1.writeMicroseconds(leg_number*3 + 1, map_(legs[leg_number].phi - phi(y,z)));;
    }
    else{
      legs[leg_number].servo1.writeMicroseconds(leg_number*3 + 1, map_(legs[leg_number].phi + phi(y,z)));;
    }
  }
  
}
void move_joint(int leg_number, double x){
  // servo3, omega // this function is incomplete right now 
  if(leg_number == 5){
    leg5.servo3.write(x);
  }
  else{
    legs[leg_number].servo1.writeMicroseconds(leg_number*3 + 2, map_(x));
  }
}

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
  legs[4].theta = 0;   // abhi calibrate  krna hai
  legs[4].phi = 0;    // abhi calibrate krna hai
  legs[4].omega = 0;

  leg5.theta = 83; 
  leg5.phi = 195;
  leg5.omega = 0;  

  // 18 pins 
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
    move_lower_leg(i,4.75,8.5);
    move_femur_leg(i,4.75,8.5);
    delay(10);
  }
  leg5.servo1.attach(9);
  leg5.servo2.attach(10);
  leg5.servo3.attach(11);
  move_lower_leg(5,4.75,8.5);
  move_femur_leg(5,4.75,8.5);
  
  Serial.begin(115200);
}


void loop() {

// stand  
  for(int i=0; i<6; i++){
    move_lower_leg(i,4.75,8.5);
    move_femur_leg(i,4.75, 8.5);
    delay(10);
  }
  delay(10000);
// sit
  for(int i=0; i<6; i++){
    move_lower_leg(i,4.75,6);
    move_femur_leg(i,4.75,6);
    delay(10);
  }
  delay(10000);
  
}












