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

void rest_position(double y, double z){
  for(int i=0; i<6; i++){
    move_lower_leg(i,y,z);
    move_femur_leg(i,y,z);
    move_joint(i, 90);
    delay(10);
  }
}

void walk_along_axis(int axis){
  //
}
void walk_along_middle_of_two_axis(int axis1, int axis2){
  //
}
void rotate(int direction, double angle){
  //
}