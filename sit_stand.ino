
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

#include <ESP32Servo.h>
#include <math.h>

struct leg{
  Servo servo1; // lower leg servo
  double theta; // calibration constant
  Servo servo2; // femur leg servo
  double phi;   // calibration constant
  Servo servo3; // joint servo
  double omega; // calibration constant
};

double x,y,z;
leg legs[6];
// leg[0] denote first leg
// leg[1] denote second leg
// ...
// leg[5] denote sixth leg

double degrees_(double radians) {
  return radians * 180.0 / M_PI;
}

double theta(double y, double z){
  return degrees_(acos((94.8125 - ((y * y) + (z * z))) / 80.75));
}
double phi(double y, double z){
  return degrees_(acos(((y * y + z * z) - 49.6875) / (9.5 * (sqrt(y * y + z * z)))) - atan2(z, y));
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
  legs[3].omega = ;
  legs[4].theta = 83;
  legs[4].phi = 190;
  legs[4].omega = 0;
  legs[5].theta = 90; 
  legs[5].phi = 195;
  legs[5].omega = 0;  
  // 18 pins 
  legs[0].servo1.attach();
  legs[0].servo2.attach();
  legs[0].servo3.attach();
  legs[1].servo1.attach();
  legs[1].servo2.attach();
  legs[1].servo3.attach();
  legs[2].servo1.attach();
  legs[2].servo2.attach();
  legs[2].servo3.attach();
  legs[3].servo1.attach();
  legs[3].servo2.attach();
  legs[3].servo3.attach();
  legs[4].servo1.attach();
  legs[4].servo2.attach();
  legs[4].servo3.attach();
  legs[5].servo1.attach();
  legs[5].servo2.attach();
  legs[5].servo3.attach();

  Serial.begin(115200);
}

void move_lower_leg(int leg_number, double y, double z){
  if(legs[leg_number].theta >= 90){
    legs[leg_number].servo1.write(legs[leg_number].theta - theta(y,z));
  }
  else{
    legs[leg_number].servo1.write(legs[leg_number].theta + theta(y,z));
  }
}
void move_femur_leg(int leg_number, double y, double z){
  if(legs[leg_number].phi >= 90){
    
    legs[leg_number].servo2.write(legs[leg_number].phi - phi(y,z));
  }
  else{
    legs[leg_number].servo2.write(legs[leg_number].phi + phi(y,z));
  }
}
void move_joint(int leg_number, double x){
  // servo3, omega
  legs[leg_number].servo3.write(x);
}
void loop() {

  // stand
  for(int i=0; i<6; i++){
    move_femur_leg(i,7,7);
    delay(50);
    move_lower_leg(i,7,7);
    delay(1000);
  }
  // sit
  for(int i=0; i<6; i++){
    move_femur_leg(i,7,4);
    delay(50);
    move_lower_leg(i,7,4);
    delay(1000)
  }
}
















