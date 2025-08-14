#include "vex.h"


bool clamped = false;
bool chomped = false;
bool doinked = false;
int clawTarget = 0;
const char * colorSortColor = "Off ";


using namespace vex;
using namespace std;
using signature = vision::signature;
using code = vision::code;



void usercontrol(void) {
    Drivetrain.setStopping(coast);
    Drivetrain.setDriveVelocity(100, pct);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);






  while (1) {
    Drivetrain.setStopping(coast);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);

    //Color sort toggle code:
    /*if (Controller1.ButtonA.pressing()) {
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
        }*/


    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(colorSortColor);
    wait(20, msec); 
                    
  }
}