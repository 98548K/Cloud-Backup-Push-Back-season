#pragma once

extern double wheelRad;

extern double resetCurrentPosition;
extern double constrainAngle(double x);


//Tuning constants:
extern double kP;
extern double kI;
extern double kD;

extern double turnKP;
extern double turnKI;
extern double turnKD;

void printAtTop(double value);

class PID {
    private:
    double p;
    double i;
    double d;
    double turnP;
    double turnI;
    double turnD;

    public:

    PID(double P, double I, double D, double TurnP, double TurnI, double TurnD);
    void turnToHeading(double desiredValue);
    void drive(double desiredValue);
    void turnToHeading(double desiredValue, double timePeriod);
    void drive(double desiredValue, double timePeriod);
    void driveWithPiston(double desiredValue, double deployRange);
};