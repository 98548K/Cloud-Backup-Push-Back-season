/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 2, 3, 4      
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

const double kp = 4;

//Basic Proportional Feedback Loop:

void driveIn(double driveDist) {
  LeftDriveSmart.setPosition(0, turns);
  RightDriveSmart.setPosition(0, turns);
  while (true) {
    LeftDriveSmart.spin(fwd, driveDist - ((((RightDriveSmart.position(turns) * (1.75 * 2) * M_PI) + (LeftDriveSmart.position(turns) * (1.75 * 2) * M_PI) / 2)) * kp), pct);
    RightDriveSmart.spin(fwd, driveDist - ((((RightDriveSmart.position(turns) * (1.75 * 2) * M_PI) + (LeftDriveSmart.position(turns) * (1.75 * 2) * M_PI) / 2)) * kp), pct);
    wait (20, msec);
    if ((((RightDriveSmart.position(turns) * (1.75 * 2) * M_PI) + (LeftDriveSmart.position(turns) * (1.75 * 2) * M_PI) / 2)) / kp >= 1) break;
  }
}

//Dumb autons because we have no extra sensors

void Dumb_Skills_Auton() {
  Drivetrain.setDriveVelocity(50, pct);
  Drivetrain.driveFor(12, inches);
  Drivetrain.setDriveVelocity(100, pct);
  Drivetrain.driveFor(-30, inches);
}

void Dumb_Match_Auton() {
  RIB.setVelocity(100, pct);
  LIB.setVelocity(100, pct);
  Drivetrain.setDriveVelocity(18, pct);
  RIB.spin(fwd);
  Drivetrain.driveFor(24, inches);
  Drivetrain.turnFor(30, deg);
  Drivetrain.driveFor(9, inches);
  RIB.spinFor(-360, deg);
  RIB.spin(fwd);
  LIB.spin(fwd);
}


void autonomous(void) {
  Dumb_Skills_Auton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
bool toggleIntakePiston;
bool deScore;

void usercontrol(void) {
  RIB.setVelocity(100, pct);
  LIB.setVelocity(100, pct);
  TIB.setVelocity(100, pct);
  // User control code here, inside the loop
  while (1) {
    
    if (Controller1.ButtonR1.pressing()){
      RIB.spin(forward);
    } else if (Controller1.ButtonR2.pressing()){
      RIB.spin(reverse);
    } else {
      RIB.stop();
    }

    if (Controller1.ButtonL1.pressing()){
      LIB.spin(forward);
      TIB.spin(forward);
    } else if (Controller1.ButtonL2.pressing()){
      LIB.spin(reverse);
      TIB.spin(reverse);
    } else {
      LIB.stop();
      TIB.stop();
    }

    if (Controller1.ButtonY.pressing()) {
      if (toggleIntakePiston == true) {
        wait (100, msec);
        toggleIntakePiston = false;
      }
      else if (toggleIntakePiston == false) {
        wait (100, msec);
        toggleIntakePiston = true;
      }
      IntakePiston.set(toggleIntakePiston);
    }


    if (Controller1.ButtonRight.pressing()) {
      if (deScore == true) {
        wait (100, msec);
        deScore = false;
      }
      else if (deScore == false) {
        wait (100, msec);
        deScore = true;
      }
      DescorePiston.set(deScore);
    }


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
