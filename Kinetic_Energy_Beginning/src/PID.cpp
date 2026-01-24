#include "vex.h"

//New re-structured PID that utilizes class usage (Still in development):
//PID_Tag is used to find all areas to add onto for additional PID with Ctrl F

//Variable declaration:
double error;
double integral;
double derivative;
double prevError;
double pwr;
double prevPwr;
double dt;
double prevTime;
double storedTrackingMeasurements;
double resetCurrentPosition;
double storedHeading;
double startTimer;
double wheelRad = 1.0;//0.0

double integralCap = 30;

double output;

//Tuning constants:
double kP = 2.3;//4.2
double kI = 0.0;//0.3
double kD = 3.8;//0.33

double turnKP = 0.4;
double turnKI;
double turnKD;


//Other tuning constants here <PID_Tag>:

double driveTolerance = 0.1;
double turnTolerance = 0.1;

//Other tolerances above <PID_Tag>:

const char* driveID = "Drive";
const char* turnID = "Turn";

//Other IDs above <PID_Tag>:

double returnSpeed;


double slewLimit = 20;

int PosNeg;
int sgn(double value) {
    if (value < 0) {
        PosNeg = -1;
    }
    else {
        PosNeg = 1;
    }
    return PosNeg;
}


void printAtTop(double value) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0,0);
    Controller1.Screen.print(value);
}


void printAtTop(const char * value) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0,0);
    Controller1.Screen.print(value);
}

//If the delta speed is greater than the slew rate, the speed will be set to the previous speed plus slew rate cap:
double slewRate(double output, double prevOutput, double error, double desiredValue) {
    //Slew rate is slewLimit% velocity
    if (output > prevOutput + slewLimit/* && std::round(error) == desiredValue*/) {
        returnSpeed = prevOutput + (slewLimit);
    }
    else if (output < prevOutput - slewLimit/* && std::round(error) == desiredValue*/) {
        returnSpeed = prevOutput - (slewLimit);
    }
    else {
        returnSpeed = output;
    }
    return returnSpeed;
}

//Function for determining the turn direction. Credit to Caleb Carlson for making this function easy to find (https://www.vexforum.com/t/turning-with-pid-how-to-find-the-shortest-turn/110258/6):
double constrainAngle(double x) {
    x = fmod(x + 180, 360);
    if (x < 0)
        x += 360;
    return x - 180;
}

void orderID(double IConstant) {
    dt = Brain.timer(sec) - prevTime;

    derivative = (error - prevError) / dt;
    integral += error * dt;
    if (std::abs(integral * IConstant) > integralCap) {
        integral = integralCap / IConstant * sgn(error);
    }
    prevTime = dt;
}

//Function that returns the output value:
double PID_math(double desiredValue, const char* assigned, double KP, double KI, double KD) {
    //Error definition using the control ID:
    //The integral capacity is 30% velocity
    if (assigned == driveID) {
        error = desiredValue - resetCurrentPosition;
        //Updates integral and derivative
        orderID(kI);
    }
    else if (assigned == turnID) {
        error = constrainAngle(desiredValue - (Inertial1.heading(deg)));
        //Updates integral and derivative
        orderID(turnKI);
    }

    //Other error updates above <PID_Tag>:

    //Previous error for finding the difference in where the robot was at and where it is at:
    prevError = error;

    //Motor output calculation:
    pwr = slewRate((error * KP) + (integral * KI) + (derivative * KD), prevPwr, error, desiredValue);


    //Return the speed:
    return pwr;
}


PID::PID(double P, double I, double D, double TurnP, double TurnI, double TurnD) {
    p = P;
    i = I;
    d = D;
    turnP = TurnP;
    turnI = TurnI;
    turnD = TurnD;
            
}

//Turn PID:
void PID::turnToHeading(double desiredValue) {
    //Turn PID loop with proper fwd/rev directional math and drivetrain motor control:
    while (true) {
        output = PID_math(desiredValue, turnID, turnP, turnI, turnD);
        LeftDriveSmart.spin(fwd, output, pct);
        RightDriveSmart.spin(reverse, output, pct);
        if (error == 0) break;
        if (error >= -turnTolerance && error <= turnTolerance) break;
        prevPwr = output;
        wait (10, msec);
    }
    LeftDriveSmart.stop(hold);
    RightDriveSmart.stop(hold);
}

//Drive PID loop with proper fwd/fwd directional math and drivetrain motor control:
void PID::drive(double desiredValue) {
    storedTrackingMeasurements = (frontTracking.position(turns)) * (wheelRad * 2) * M_PI;
    storedHeading = Inertial1.heading(deg);
    startTimer = Brain.timer(sec);
    Brain.resetTimer();
    while (true) {
        resetCurrentPosition = ((frontTracking.position(turns)) * (wheelRad * 2) * M_PI) - storedTrackingMeasurements;
        output = PID_math(desiredValue, driveID, p, i, d);
        LeftDriveSmart.spin(fwd, output + constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.1, pct);
        RightDriveSmart.spin(fwd, output - constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.1, pct);
        if (error >= -driveTolerance && error <= driveTolerance) break;
        prevPwr = output;
        wait (10, msec);
    }
    LeftDriveSmart.stop(hold);
    RightDriveSmart.stop(hold);
    Brain.setTimer(Brain.timer(sec) + startTimer, sec);
}

//Turn PID with timer:
void PID::turnToHeading(double desiredValue, double timePeriod) {
    //Turn PID loop with proper fwd/rev directional math and drivetrain motor control:
    startTimer = Brain.timer(sec);
    Brain.resetTimer();
    while (true) {
        output = PID_math(desiredValue, turnID, turnP, turnI, turnD);
        LeftDriveSmart.spin(fwd, output, pct);
        RightDriveSmart.spin(reverse, output, pct);
        if (Brain.timer(sec) <= timePeriod + 0.1 && Brain.timer(sec) >= timePeriod - 0.1) break;
        prevPwr = output;
        wait (10, msec);
    }
    LeftDriveSmart.stop(hold);
    RightDriveSmart.stop(hold);
    Brain.setTimer(Brain.timer(sec) + startTimer, sec);
}

//Drive PID loop with proper fwd/fwd directional math and drivetrain motor control with timer:
void PID::drive(double desiredValue, double timePeriod) {
    storedTrackingMeasurements = (frontTracking.position(turns)) * (wheelRad * 2) * M_PI;
    storedHeading = Inertial1.heading(deg);
    startTimer = Brain.timer(sec);
    Brain.resetTimer();
    while (true) {
        resetCurrentPosition = ((frontTracking.position(turns)) * (wheelRad * 2) * M_PI) - storedTrackingMeasurements;
        output = PID_math(desiredValue, driveID, p, i, d);
        LeftDriveSmart.spin(fwd, output + constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.1, pct);
        RightDriveSmart.spin(fwd, output - constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.1, pct);
        if (Brain.timer(sec) <= timePeriod + 0.1 && Brain.timer(sec) >= timePeriod - 0.1) break;
        prevPwr = output;
        wait (10, msec);
    }
    LeftDriveSmart.stop(hold);
    RightDriveSmart.stop(hold);
    Brain.setTimer(Brain.timer(sec) + startTimer, sec);
}


void PID::driveWithPiston(double desiredValue, double deployRange) {
    storedTrackingMeasurements = (frontTracking.position(turns)) * (wheelRad * 2) * M_PI;
    storedHeading = Inertial1.heading(deg);
    while (true) {
        resetCurrentPosition = ((frontTracking.position(turns)) * (wheelRad * 2) * M_PI) - storedTrackingMeasurements;
        LeftDriveSmart.spin(fwd, PID_math(desiredValue, driveID, p, i, d), pct);
        RightDriveSmart.spin(fwd, PID_math(desiredValue, driveID, p, i, d), pct);
        if (error == 0) break;
        if (error <= deployRange) DescorePiston.set(true);
        if (error >= -driveTolerance && error <= driveTolerance) break;
        printAtTop(frontTracking.position(turns));
        prevPwr = output;
        wait (10, msec);
    }
    LeftDriveSmart.stop(hold);
    RightDriveSmart.stop(hold);
}

//Other functions above <PID_Tag>:
