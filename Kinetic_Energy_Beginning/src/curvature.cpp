#include "vex.h"


const double curveKP = 3.0; //0.0
const double curveKI = 0.0; //0.0
const double curveKD = 0.0; //0.0

const double integralLimit = 10.0; //10.0
const double curveTolerance = 2.0; //2.0

void curveToPosition(double desiredX, double desiredY) {
    double LIntegral = 0;
    double RIntegral = 0;

    double LError = 0.0;
    double RError = 0.0;

    LeftDriveSmart.setPosition(0, turns);
    RightDriveSmart.setPosition(0, turns);

    double LDesiredCurve = getDistance(leftDriveX, leftDriveY, desiredX, desiredY);
    double RDesiredCurve = getDistance(rightDriveX, rightDriveY, desiredX, desiredY);

    while (true) {
        LError = getDistance(leftDriveX, leftDriveY, desiredX, desiredY);
        RError = getDistance(rightDriveX, rightDriveY, desiredX, desiredY);

        LIntegral += LError;
        RIntegral += RError;

        double LPrevError = LError;
        double RPrevError = RError;

        double LDerivative = LError - LPrevError;
        double RDerivative = RError - RPrevError;


        double LPwr = LError * curveKP + LIntegral * curveKI + LDerivative * curveKD;
        double RPwr = RError * curveKP + RIntegral * curveKI + RDerivative * curveKD;


        LeftDriveSmart.spin(fwd, LPwr, pct);
        RightDriveSmart.spin(fwd, RPwr, pct);

        //Integral limit stuff:
        if ((std::abs(LError) < integralLimit) && (std::abs(RError) < integralLimit)) {
            LIntegral = 0;
            RIntegral = 0;
        } else if (std::abs(LError) < integralLimit) {
            LIntegral = 0;
            RIntegral = 0;
        }

        std::cout << "Power: " << LPwr << " " << RPwr << " Error " << LError << " " << RError << std::endl;

        //std::round(X) == std::round(desiredX) && std::round(Y) == std::round(desiredY)
        //(LError >= -curveTolerance && LError <= curveTolerance) || (RError <= curveTolerance && RError >= -curveTolerance)
        
        if (Inertial1.heading(deg) >= 90 && Inertial1.heading(deg) < 110) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }


        wait (20, msec);
    }
}