double phi(double y, double z);
double theta(double y, double z);
void move_lower_leg(int leg_number, double y, double z);
void move_femur_leg(int leg_number, double y, double z);
void move_joint(int leg_number, double x);
void rest_position(double y, double z);
void walk_along_axis(int axis); 
void walk_along_middle_of_two_axis(int axis1, int axis2);

// leg1-leg4 -> Axis 1
// leg2-leg5 -> Axis 2
// leg3-leg6 -> Axis 3
