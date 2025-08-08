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

//manual controls
void toggleClamp() {
    if (clamped == true) {
        clamped = false;
        wait (.22, sec);
    }
    else if (clamped == false) {
        clamped = true;
        wait (.22, sec);
    }
    Clamp.set(clamped);
}


void toggleClawUpState() {
    clawTarget++;

    if (clawTarget == 3) {
        clawTarget = 1;
    }
}



void toggleDoinker() {
    if (doinked == true) {
        doinked = false;
        wait (.22, sec);
    }
    else if (doinked == false) {
        doinked = true;
        wait (.22, sec);
    }
    Doinker.set(doinked);
}


void toggleTeeth() {
    if (chomped == true) {
        chomped = false;
        wait (.22, sec);
    }
    else if (chomped == false) {
        chomped = true;
        wait (.22, sec);
    }
    Teeth.set(chomped);
}


void clawDown() {
    clawTarget = 0;
}



float targetAngle;
float clawError;



void usercontrol(void) {
    Drivetrain.setStopping(coast);
    Drivetrain.setDriveVelocity(100, pct);
    Intakes.setVelocity(100, pct);
    frontTracking.setPosition(0, deg);
    sideTracking.setPosition(0, deg);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);
    Claw.setVelocity(100, pct);
    ringOptical.setLightPower(100, pct);
    Claw.setMaxTorque(100, pct);
    Claw.setPosition(10, deg);




    //Task declaration
    task colorSortingBlue = task (colorSortBlue);
    task colorSortingRed = task (colorSortRed);

    colorSortingBlue.suspend();
    colorSortingRed.suspend();


  while (1) {
    Drivetrain.setStopping(coast);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);



    colorSort.set(false);







    //Color sort toggle code
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
    }


    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(colorSortColor);
    wait(20, msec); 
                    
  }
}