extern double wheelRad;
extern const double drivetrainWidth;
extern const double drivetrainLength;
extern double resetCurrentPosition;

void driveIn(double driveDist);

void turnToHeading(double turnHeading);

void driveIn(double driveDist, double drivePeriod);

void turnToHeading(double turnHeading, double turnPeriod);

void driveInWithPiston(double driveDist, double DeployRange);

extern double constrainAngle(double x);

extern double turnKP;
extern double turnKI;
extern double turnKD;

extern double kP;
extern double kI;
extern double kD;

extern double storedTrackingMeasurements;
extern double resetCurrentPosition;

extern double turnIntegralLimit;
extern double driveIntegralLimit;

void longDrive();

void shortDrive();

void longTurn();

void shortTurn();