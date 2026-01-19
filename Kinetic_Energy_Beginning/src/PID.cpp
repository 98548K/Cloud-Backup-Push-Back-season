#include "vex.h"


//Tuning constants
double kP;
double kI;
double kD;

void setDriveConstants(double dP, double dI, double dD) {
    kP = dP;
    kI = dI;
    kD = dD;
}


double turnKP;
double turnKI;
double turnKD;


void setTurnConstants(double tP, double tI, double tD) {
    turnKP = tP;
    turnKI = tI;
    turnKD = tD;
}

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

double wheelRad = 1.0;//0.0

double turnTolerance = 1.0;//0.5
double driveTolerance = 0.5;//0.25

const double drivetrainWidth = 13.0;//↔
const double drivetrainLength = 15.5;//↕

double resetCurrentPosition;

//Function for determining the turn direction. Credit to Caleb Carlson for making this function easy to find (https://www.vexforum.com/t/turning-with-pid-how-to-find-the-shortest-turn/110258/6):
double constrainAngle(double x) {
    x = fmod(x + 180, 360);
    if (x < 0)
        x += 360;
    return x - 180;
}

double returnSpeed;


double slewLimit = 20;


//If the delta speed is greater than the slew rate, the speed will be set to the previous speed plus slew rate cap:
double slewRate(double output, double prevOutput, double error, double desiredValue) {
    //Slew rate is slewRange% velocity
    if (output > prevOutput + slewLimit && std::round(error) != desiredValue) {
        returnSpeed = prevOutput + (slewLimit);
    }
    else if (output < prevOutput - slewLimit && std::round(error) != desiredValue) {
        returnSpeed = prevOutput - (slewLimit);
    }
    else {
        returnSpeed = output;
    }
    return returnSpeed;
}



//PID class initialization:
class PID {
    //Declaring all instances in the class. (eg. PID math variables):
    private:
        //Declaring multiplication constants:
        //Declaring sensor math variables:
        double desiredValue;
        double error;
        double integral;
        double derivative;
        double pwr;
        double prevError;
        double storedTrackingMeasurements;
        double storedHeading;
        double timing;
        double deployRange;
        double prevPwr;
        //Declaring what instance of motor control it is:
        bool timerEnabled;
        bool isTurning;
        bool isDriving;
    //PID class parameter setup:
    public:
        PID(double DesiredValue, bool IsDriving, bool IsTurning, bool TimerEnabled, double Timing, double DeployRange) {
            desiredValue = DesiredValue;
            error = DesiredValue;
            isTurning = IsTurning;
            isDriving = IsDriving;
            timerEnabled = TimerEnabled;
            timing = Timing;
            deployRange = DeployRange;
        }

        void run() {
            integral = 0;
            error = 0;
            //This accounts for the tracking wheel measuremants in PID:
            storedTrackingMeasurements = (frontTracking.position(turns)) * (wheelRad * 2) * M_PI;

            storedHeading = Inertial1.heading(deg);
            while (true) {
                //This simmulates drive PID starting at 0:
                resetCurrentPosition = ((frontTracking.position(turns)) * (wheelRad * 2) * M_PI) - storedTrackingMeasurements;

                //This is nescessarry for odometry to work so we don't have to reset the forward/sideways tracking position.
                //It instead starts where the tracking position is to 0 allowing it to use distance values instead of coordinate values.

                //PID math:

                integral = 0;// += error;
                //

                
                if (std::abs(integral * kI) > 30 && isDriving) {
                    integral = 30 / kI * sgn(error);
                }
                else if (std::abs(integral * turnKI) > 30 && isTurning) {
                    integral = 30 / turnKI;
                }
                

                //More PID math:
                derivative = error - prevError;
                //



                //Class initialization for turning:
                if (isTurning && !timerEnabled) {
                    error = constrainAngle(desiredValue - (Inertial1.heading(deg)));
                    pwr = (error * turnKP) + (integral * turnKI) + (derivative * turnKD);
                    LeftDriveSmart.spin(fwd, slewRate(pwr, prevPwr, error, desiredValue), pct);
                    RightDriveSmart.spin(reverse, slewRate(pwr, prevPwr, error, desiredValue), pct);
                    if (error == 0) break;
                    if (error >= -turnTolerance && error <= turnTolerance) break;
                }

                //If it messes up the acceleration or measurement values use this:
                //LeftDriveSmart.spin(fwd, pwr, pct);
                //RightDriveSmart.spin(fwd, pwr, pct);

                //Class initialization for driving:
                else if (isDriving && !timerEnabled) {
                    //This section is just drive PID:
                    error = desiredValue - resetCurrentPosition;
                    pwr = (error * kP) + (derivative * kD);
                    RightDriveSmart.spin(fwd, (slewRate(pwr, prevPwr, error, desiredValue) - constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.5), pct);
                    LeftDriveSmart.spin(fwd, (slewRate(pwr, prevPwr, error, desiredValue) + constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.5), pct);
                    if (error == 0) break;
                    if (error >= -driveTolerance && error <= driveTolerance) break;
                }


                //Class initialization for turning with timer:
                if (isTurning && timerEnabled) {
                    error = constrainAngle(desiredValue - (Inertial1.heading(deg)));
                    pwr = error * turnKP + integral * turnKI + derivative * turnKD;
                    LeftDriveSmart.spin(fwd, slewRate(pwr, prevPwr, error, desiredValue), pct);
                    RightDriveSmart.spin(reverse, slewRate(pwr, prevPwr, error, desiredValue), pct);
                    if (Brain.timer(sec) <= timing + 0.1 && Brain.timer(sec) >= timing - 0.1) break;
                }


                //Class initialization for driving with timer:
                else if (isDriving && timerEnabled) {
                    //This section is just drive PID:
                    error = desiredValue - resetCurrentPosition;
                    pwr = error * kP + integral * kI + derivative * kD;
                    RightDriveSmart.spin(fwd, slewRate(pwr, prevPwr, error, desiredValue), pct);
                    LeftDriveSmart.spin(fwd, slewRate(pwr, prevPwr, error, desiredValue), pct);
                    if (Brain.timer(sec) <= timing + 0.1 && Brain.timer(sec) >= timing - 0.1) break;
                }

                else if (isDriving && deployRange < desiredValue) {
                    //This section is just drive PID:
                    error = desiredValue - resetCurrentPosition;
                    pwr = error * kP + integral * kI + derivative * kD;
                    RightDriveSmart.spin(fwd, slewRate(pwr, prevPwr, error, desiredValue), pct);
                    LeftDriveSmart.spin(fwd, slewRate(pwr, prevPwr, error, desiredValue), pct);
                    if (error == 0) break;
                    if (error <= deployRange) DescorePiston.set(true);
                    if (error >= -driveTolerance && error <= driveTolerance) break;
                }

                wait (10, msec);
                prevPwr = pwr;
                prevError = error;
            }
            LeftDriveSmart.stop(hold);
            RightDriveSmart.stop(hold);
        }
};

//Drive PID function:
void driveIn(double driveDist) {
    PID drivePID(driveDist, true, false, false, 0, driveDist);
    drivePID.run();
}

//Turn PID function:
void turnToHeading(double turnHeading) {
    PID turnPID(turnHeading, false, true, false, 0, 0);
    turnPID.run();
}

double startTimer;

//Drive PID with timer function:
void driveIn(double driveDist, double drivePeriod) {
    startTimer = Brain.timer(sec);
    Brain.resetTimer();
    PID timedDrivePID(driveDist, true, false, true, drivePeriod, driveDist);
    timedDrivePID.run();
    Brain.setTimer(Brain.timer(sec) + startTimer, sec);
}

//Turn PID with timer function:
void turnToHeading(double turnHeading, double turnPeriod) {
    startTimer = Brain.timer(sec);
    Brain.resetTimer();
    PID timedTurnPID(turnHeading, false, true, true, turnPeriod, 0);
    timedTurnPID.run();
    Brain.setTimer(Brain.timer(sec) + startTimer, sec);
}


void driveInWithPiston(double driveDist, double DeployRange) {
    PID drivePID(driveDist, true, false, false, 0, DeployRange);
    drivePID.run();
}
/*


//New re-structured PID that utilizes class usage (Still in development):

//Variable declaration:
double error;
double integral;
double derivative;
double prevError;
double pwr;
double prevPwr;
double resetCurrentPosition;
double storedHeading;
double startTimer;
double wheelRad = 1.0;//0.0

double driveTolerance = 0.0;
double turnTolerance = 0.0;


const char* driveID = "Drive";
const char* turnID = "Turn";

//Function that returns the output value:
double PID_math(double desiredValue, const char* assigned, double kP, double kI, double kD) {
    //Integral limit pizzaz:
    integral += error;

    //Error definition using the control ID:
    //The integral capacity is 30% velocity
    if (assigned = driveID) {
        error = desiredValue - resetCurrentPosition;
        if (std::abs(integral * kI) > 30) {
            integral = 30 / kI * sgn(error);
        }
    }
    else if (assigned = turnID) {
        error = constrainAngle(desiredValue - std::abs(Inertial1.heading(deg)));
        if (std::abs(integral * turnKI) > 30) {
            integral = 30 / turnKI * sgn(error);
        }
    }
    //Previous error for finding the difference in where the robot was at and where it is at:
    prevError = error;
    

    //Derivative update:
    derivative = error - prevError;

    //Motor output calculation:
    pwr = slewRate((error * kP) + (integral * kI) + (derivative * kD), prevPwr, error, desiredValue);


    //Return the speed:
    return pwr;
}

//Function for determining the turn direction. Credit to Caleb Carlson for making this function easy to find (https://www.vexforum.com/t/turning-with-pid-how-to-find-the-shortest-turn/110258/6):
double constrainAngle(double x) {
    x = fmod(x + 180, 360);
    if (x < 0)
        x += 360;
    return x - 180;
}

double returnSpeed;


double slewLimit = 20;


//If the delta speed is greater than the slew rate, the speed will be set to the previous speed plus slew rate cap:
double slewRate(double output, double prevOutput, double error, double desiredValue) {
    //Slew rate is slewRange% velocity
    if (output > prevOutput + slewLimit && std::round(error) != desiredValue) {
        returnSpeed = prevOutput + (slewLimit);
    }
    else if (output < prevOutput - slewLimit && std::round(error) != desiredValue) {
        returnSpeed = prevOutput - (slewLimit);
    }
    else {
        returnSpeed = output;
    }
    return returnSpeed;
}


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


//Class for PID and maybe other actions
class PID {
    private:
        //Variables used only inside the class: 
        double p;
        double i;
        double d;
        double turnP;
        double turnI;
        double turnD;

    public:
        //PID constants are tuned here:
        PID(double P, double I, double D, double TurnP, double TurnI, double TurnD) {
            p = P;
            i = I;
            d = D;
            turnP = TurnP;
            turnI = TurnI;
            turnD = TurnD;
            
        }

        //Turn PID:
        void turnToHeading(double desiredValue) {
            //Turn PID loop with proper fwd/rev directional math and drivetrain motor control:
            while (true) {
                LeftDriveSmart.spin(fwd, PID_math(desiredValue, turnID, p, i, d), pct);
                RightDriveSmart.spin(reverse, PID_math(desiredValue, turnID, p, i, d), pct);
                if (error == 0) break;
                if (desiredValue - constrainAngle(desiredValue - std::abs(Inertial1.heading(deg))) >= -turnTolerance && desiredValue - constrainAngle(desiredValue - std::abs(Inertial1.heading(deg))) <= turnTolerance) break;
                wait (10, sec);
            }
            LeftDriveSmart.stop(hold);
            RightDriveSmart.stop(hold);
        }

        //Drive PID loop with proper fwd/fwd directional math and drivetrain motor control:
        void drive(double desiredValue) {
            storedTrackingMeasurements = std::abs(frontTracking.position(turns)) * (wheelRad * 2) * M_PI;
            storedHeading = Inertial1.heading(deg);
            while (true) {
                resetCurrentPosition = (std::abs(frontTracking.position(turns)) * (wheelRad * 2) * M_PI) - storedTrackingMeasurements;
                LeftDriveSmart.spin(fwd, PID_math(desiredValue, driveID, p, i, d) - constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.1, pct);
                RightDriveSmart.spin(fwd, PID_math(desiredValue, driveID, p, i, d) + constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.1, pct);
                if (error == 0) break;
                if (desiredValue - resetCurrentPosition >= -driveTolerance && desiredValue - resetCurrentPosition <= driveTolerance) break;
                wait (10, sec);
            }
            LeftDriveSmart.stop(hold);
            RightDriveSmart.stop(hold);
        }

        //Turn PID loop with proper fwd/rev directional math and drivetrain motor control with timer:
        void turnToHeading(double desiredValue, double timePeriod) {
            startTimer = Brain.timer(sec);
            Brain.resetTimer();
            while (true) {
                LeftDriveSmart.spin(fwd, PID_math(desiredValue, turnID, p, i, d), pct);
                RightDriveSmart.spin(reverse, PID_math(desiredValue, turnID, p, i, d), pct);
                if (Brain.timer(sec) <= timePeriod + 0.1 && Brain.timer(sec) >= timePeriod - 0.1) break;
                wait (10, sec);
            }
            LeftDriveSmart.stop(hold);
            RightDriveSmart.stop(hold);
            Brain.setTimer(Brain.timer(sec) + startTimer, sec);
        }

        //Drive PID loop with proper fwd/fwd directional math and drivetrain motor control with timer:
        void drive(double desiredValue, double timePeriod) {
            storedTrackingMeasurements = std::abs(frontTracking.position(turns)) * (wheelRad * 2) * M_PI;
            storedHeading = Inertial1.heading(deg);
            startTimer = Brain.timer(sec);
            Brain.resetTimer();
            while (true) {
                resetCurrentPosition = (std::abs(frontTracking.position(turns)) * (wheelRad * 2) * M_PI) - storedTrackingMeasurements;
                LeftDriveSmart.spin(fwd, PID_math(desiredValue, driveID, p, i, d) - constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.1, pct);
                RightDriveSmart.spin(fwd, PID_math(desiredValue, driveID, p, i, d) + constrainAngle(storedHeading - Inertial1.heading(deg)) * 0.1, pct);
                if (Brain.timer(sec) <= timePeriod + 0.1 && Brain.timer(sec) >= timePeriod - 0.1) break;
                wait (10, sec);
            }
            LeftDriveSmart.stop(hold);
            RightDriveSmart.stop(hold);
            Brain.setTimer(Brain.timer(sec) + startTimer, sec);
        }
};

//Chassis declaration:
PID chassis(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
*/