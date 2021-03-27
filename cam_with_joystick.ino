#include <Stepper.h>
#include <ros.h>
//#include <std_msgs/String.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Float32.h>

//when try to do two, got problem

const int stepsRev = 1024;
const int stepsRev2 = 1024;
Stepper myStepper = Stepper(stepsRev, 8, 10, 9, 11);
Stepper myStepper2 = Stepper(stepsRev2, 2, 4, 3, 5);

//int activate = 0;
bool pan_l = false;
bool pan_r = false;
bool tilt_u = false;
bool tilt_d = false;

ros::NodeHandle nh;

void joydata( const sensor_msgs::Joy& joy) {

  if ((joy.axes[3] > 0 && joy.axes[3] <= 1)) {
        //activate = 1;
        pan_l = true;
  } else if ((joy.axes[3] < 0 && joy.axes[3] >= -1)) {
        pan_r = true;
        //activate = 2;    
  } else if ((joy.axes[4] > 0 && joy.axes[4] <= 1)) {
        tilt_u = true;
  } else if ((joy.axes[4] < 0 && joy.axes[4] >= -1)) {
        tilt_d = true;
  }

}

void pan_anticlock() {
  
  myStepper2.step(10);
  pan_l = false;
  //activate = 0;
  }

void pan_clock() {

  myStepper2.step(-10);
  pan_r = false;
  //activate = 0;
  }

void tilt_up() {

  myStepper.step(10);
  tilt_u = false;
}

void tilt_down() {
  myStepper.step(-10);
  tilt_d = false;
}


ros::Subscriber<sensor_msgs::Joy> sub1("joy", &joydata); //Adjust speed here for overall speed

void setup() {
  myStepper.setSpeed(10);
  myStepper2.setSpeed(10);
  nh.initNode();
  nh.subscribe(sub1);
   // Begin Serial communication at a baud rate of 57600:
  Serial.begin(57600);
}

void loop() {
  if (pan_l) {
    pan_anticlock();
  } else if (pan_r) {
    pan_clock();
  } else if (tilt_u) {
    tilt_up();
  } else if (tilt_d) {
    tilt_down();
  }
  
  /*switch (activate) {
    case 1://problem
    pan_anticlock();
    
    case 2:
    pan_clock();
  }*/
  
  nh.spinOnce();
  //delay(1);
}
