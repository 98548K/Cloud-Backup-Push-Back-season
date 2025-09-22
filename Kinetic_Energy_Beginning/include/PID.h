extern double wheelRad;
extern const double drivetrainWidth;
extern const double drivetrainLength;

void driveIn(double driveDist);

void turnToHeading(double turnHeading);

void driveInOdom(double driveDist);

void slowDriveOdom(double driveDist);

void slowDrive(double driveDist);

extern double constrainAngle(double x);

extern double turnKP;
extern double turnKI;
extern double turnKD;

extern double kP;
extern double kI;
extern double kD;

extern double storedTrackingMeasurements;
extern double resetCurrentPosition;