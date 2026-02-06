extern double FRONT_WHEEL;
extern double SIDE_WHEEL;
extern double X;
extern double Y;
extern double radianHeading;
extern double horizontalTrackingCenter;
extern double verticalTrackingCenter;
extern int positionTracking();
void setDrivePosition(double x, double y);
void turnToPosition(double x, double y, vex::directionType dir);
void turnToPosition(double x, double y, vex::directionType dir, double Limer);
void driveToPosition(double x, double y, vex::directionType dir);
void driveToPosition(double x, double y, vex::directionType dir, double Limer);
extern double getDistance(double x1, double y1, double x2, double y2);
extern double leftDriveFrontX;
extern double leftDriveFrontY;
extern double rightDriveFrontX;
extern double rightDriveFrontY;

extern double leftDriveBackX;
extern double leftDriveBackY;
extern double rightDriveBackX;
extern double rightDriveBackY;

extern double offsetGPS1X;
extern double offsetGPS1Y;

extern double offsetGPS2X;
extern double offsetGPS2Y;