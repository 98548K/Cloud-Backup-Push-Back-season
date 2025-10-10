#include "vex.h"


const char * colorSortColor = "Off ";


using namespace vex;
using namespace std;
using signature = vision::signature;
using code = vision::code;

bool toggleIntakePiston;
bool deScore;
bool wingIt;



void usercontrol(void) {
    Drivetrain.setStopping(coast);
    Drivetrain.setDriveVelocity(100, pct);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);
    TopIntake.setVelocity(100, pct);
    BottomIntake.setVelocity(100, pct);
    ReversedIntake.setVelocity(100, pct);



  while (1) {
    Drivetrain.setStopping(coast);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);


    if (Controller1.ButtonR1.pressing()){
      BottomIntake.spin(fwd);
      ReversedIntake.spin(fwd);
    } else if (Controller1.ButtonR2.pressing()){
      BottomIntake.spin(reverse);
      ReversedIntake.spin(reverse);
    } else {
      BottomIntake.stop();
      ReversedIntake.stop();
    }
    
    if (Controller1.ButtonL1.pressing()){
      TopIntake.spin(fwd);
    } else if (Controller1.ButtonL2.pressing()){
      TopIntake.spin(reverse);
    } else {
      TopIntake.stop();
    }

    if (Controller1.ButtonY.pressing()) {
      if (toggleIntakePiston == true) {
        toggleIntakePiston = false;
        wait (200, msec);
      }
      else if (toggleIntakePiston == false) {
        toggleIntakePiston = true;
        wait (200, msec);
      }
      IntakePiston.set(toggleIntakePiston);
    }


    if (Controller1.ButtonRight.pressing()) {
      if (deScore == true) {
        deScore = false;
        wait (200, msec);
      }
      else if (deScore == false) {
        deScore = true;
        wait (200, msec);
      }
      DescorePiston.set(deScore);
    }

    if (Controller1.ButtonB.pressing()) {
      if (wingIt == true) {
        wingIt = false;
        wait (200, msec);
      }
      else if (wingIt == false) {
        wingIt = true;
        wait (200, msec);
      }
      Wing.set(wingIt);
    }
    
    //Color sort toggle code:
    if (Controller1.ButtonA.pressing()) {
        if (colorSortColor == "Off ") {
            colorSortColor = "Red ";
            colorSortingBlue.suspend();
            colorSortingRed.resume();
            wait (.22, sec);
        }
        else if (colorSortColor == "Red ") {
            colorSortColor = "Blue";
            colorSortingBlue.resume();
            colorSortingRed.suspend();
            wait (.22, sec);
        }
        else if (colorSortColor == "Blue") {
            colorSortColor = "Off ";
            colorSortingBlue.suspend();
            colorSortingRed.suspend();
            wait (.22, sec);
        }
        else {
            colorSortColor = "Off ";
        }

    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(colorSortColor);
    wait(20, msec); 
                    
  }
}
}