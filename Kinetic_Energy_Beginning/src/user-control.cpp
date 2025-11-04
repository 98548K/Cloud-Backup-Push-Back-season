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
    FrontIntake.setVelocity(100, pct);
    MiddleIntake.setVelocity(100, pct);
    BackIntake.setVelocity(100, pct);
    BorderControl.setLightPower(100, pct);



  while (1) {
    Drivetrain.setStopping(coast);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);

    if (Controller1.ButtonR1.pressing() && Controller1.ButtonL1.pressing()) {
      BackIntake.spin(reverse, 100, pct);
      MiddleIntake.spin(fwd, 100, pct);
      FrontIntake.spin(fwd, 100, pct);
    }
    else if (Controller1.ButtonR1.pressing() && Controller1.ButtonL2.pressing()) {
      BackIntake.spin(fwd, 100, pct);
      MiddleIntake.spin(fwd, 100, pct);
      FrontIntake.spin(fwd, 100, pct);
    }
    //Intake fill
    else if (Controller1.ButtonR1.pressing()){
      BackIntake.stop();
      MiddleIntake.spin(fwd, 100, pct);
      FrontIntake.spin(fwd, 100, pct);
    }
    //Outtake
    else if (Controller1.ButtonR2.pressing()){
      BackIntake.stop();
      MiddleIntake.spin(reverse, 100, pct);
      FrontIntake.spin(reverse, 100, pct);
    }
    //Intake long
    else if (Controller1.ButtonL1.pressing()){
      BackIntake.spin(reverse, 100, pct);
      MiddleIntake.stop();
      FrontIntake.stop();
    }
    //Intake medium
    else if (Controller1.ButtonL2.pressing()){
      BackIntake.spin(fwd, 100, pct);
      MiddleIntake.stop();
      FrontIntake.stop();
    }
    //Stop intakes
    else {
      BackIntake.stop();
      MiddleIntake.stop();
      FrontIntake.stop();
    }


    if (Controller1.ButtonDown.pressing()) {
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