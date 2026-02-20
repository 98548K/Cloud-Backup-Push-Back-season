#include "vex.h"



const char * colorSortColor = "Off ";


using namespace vex;
using namespace std;
using signature = vision::signature;
using code = vision::code;

//Used for some weird controls that josh likes for some reason
bool toggleIntakePiston;

//Counters for toggling
bool wingBool = false;
bool descoreBool = false;
bool intakePistonBool = false;
bool speedBool = false;

//Drivetrain speed is divisible by half
double half = 1;


//Motor controls
void intakeFill() {
  TopIntakePiston.set(false);
  BackIntake.stop();
  MiddleIntake.spin(fwd, 100, pct);
  FrontIntake.spin(fwd, 100, pct);
}

void outtake() {
  if (intakePistonBool == false) {
    TopIntakePiston.set(false);
    BackIntake.stop();
    MiddleIntake.spin(reverse, 100, pct);
    FrontIntake.spin(reverse, 100, pct);
  }
  else {
    TopIntakePiston.set(false);
    BackIntake.stop();
    MiddleIntake.spin(reverse, 100, pct);
    FrontIntake.spin(reverse, 50, pct);
  }
}

void intakeLong() {
  BackIntake.spin(reverse, 25, pct);
  MiddleIntake.stop();
  FrontIntake.stop();
  wait (15, msec);
  TopIntakePiston.set(true);
}

void intakeMedium() {
  BackIntake.spin(fwd, 90, pct);
  MiddleIntake.stop();
  FrontIntake.stop();
  wait (15, msec);
  TopIntakePiston.set(true);
}

void stopIntakes() {
  TopIntakePiston.set(false);
  BackIntake.stop();
  MiddleIntake.stop();
  FrontIntake.stop();
}

//Button toggle callbacks
void setWing() {
  wingBool = !wingBool;
  Wing.set(wingBool);
}

void setDescore() {
  descoreBool = !descoreBool;
  DescorePiston.set(descoreBool);
}

void setIntakePiston() {
  intakePistonBool = !intakePistonBool;
  BottomIntakePiston.set(intakePistonBool);

}

void runAuton() {
  setDriveConstants(3.0, 0.01, 0.0);
  setTurnConstants(0.4075, 0.01, 0.79);
  Inertial1.setHeading(skills_.selectedHeading(), deg);
  setDrivePosition(skills_.selectedX(), skills_.selectedY());
  wait (3, sec);
  Brain.resetTimer();
  trackingWheelPiston.set(false);
  Skills();
  trackingWheelPiston.set(true);
}

void setSpeed() {
  speedBool = !speedBool;
  if (speedBool == false) {
    half = 1;
  }
  else if (speedBool == true) {
    half = 4.5;
  }
}

void setColor() {
  if (colorSortColor == "Off ") {
    colorSortColor = "Red ";
    colorSortingBlue.suspend();
    colorSortingRed.resume();
  }
  else if (colorSortColor == "Red ") {
    colorSortColor = "Blue";
    colorSortingBlue.resume();
    colorSortingRed.suspend();
  }
  else if (colorSortColor == "Blue") {
    colorSortColor = "Off ";
    colorSortingBlue.suspend();
    colorSortingRed.suspend();
  }
  else {
    colorSortColor = "Off ";
  }

    

  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print(colorSortColor);
}

void usercontrol(void) {
    setDriveConstants(2.5, 0.9, 2.8);
    setTurnConstants(0.4, 0.00027, 0.7);
    Drivetrain.setStopping(coast); 
    Drivetrain.setDriveVelocity(100, pct);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);
    FrontIntake.setVelocity(100, pct);
    MiddleIntake.setVelocity(100, pct);
    BackIntake.setVelocity(100, pct);
    trackingWheelPiston.set(true);
    //Button toggles
    Controller1.ButtonY.pressed(setWing);
    Controller1.ButtonRight.pressed(setDescore);
    Controller1.ButtonDown.pressed(setIntakePiston);
    Controller1.ButtonX.pressed(setSpeed);
    Controller1.ButtonB.pressed(setColor);


  while (1) {
    Drivetrain.setStopping(coast);
    LeftDriveSmart.setStopping(coast);
    RightDriveSmart.setStopping(coast);

    if (Controller1.ButtonLeft.pressing()) {
      runAuton();
    }


    if (Controller1.ButtonR1.pressing() && Controller1.ButtonL1.pressing()) {
      BackIntake.spin(reverse, 100, pct);
      MiddleIntake.spin(fwd, 100, pct);
      FrontIntake.spin(fwd, 100, pct);
      wait (15, msec);
      TopIntakePiston.set(true);
    }
    else if (Controller1.ButtonR1.pressing() && Controller1.ButtonL2.pressing()) {
      BackIntake.spin(fwd, 40, pct);
      MiddleIntake.spin(fwd, 100, pct);
      FrontIntake.spin(fwd, 100, pct);
      wait (15, msec);
      TopIntakePiston.set(true);
    }
    else if (Controller1.ButtonR2.pressing() && Controller1.ButtonL2.pressing()) {
      BackIntake.spin(reverse, 100, pct);
      MiddleIntake.spin(reverse, 100, pct);
      FrontIntake.spin(reverse, 100, pct);
    }
    else if (Controller1.ButtonR2.pressing() && Controller1.ButtonL1.pressing()) {
      BackIntake.spin(fwd, 90, pct);
      MiddleIntake.spin(reverse, 100, pct);
      FrontIntake.spin(reverse, 100, pct);
    }
    //Intake fill
    else if (Controller1.ButtonR1.pressing()){
      intakeFill();
    }
    //Outtake
    else if (Controller1.ButtonR2.pressing()){
      outtake();
    }
    //Intake medium
    else if (Controller1.ButtonL1.pressing()){
      intakeLong();
    }
    //Intake long
    else if (Controller1.ButtonL2.pressing()){
      intakeMedium();
    }
    //Stop intakes
    else {
      stopIntakes();
    }

    task::sleep(10);
  }
}