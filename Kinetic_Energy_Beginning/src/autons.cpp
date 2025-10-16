#include "vex.h"

double beginHeading;

void Right_Blue() {
    
    beginHeading = 270;
    X = 63.8;
    Y = 17;
    Inertial1.setHeading(beginHeading, deg);
    wait (3, sec);

    ReversedIntake.spin(fwd, 100, pct);
    BottomIntake.spin(fwd, 100, pct);
    turnCurveP = 0.6;
    tracePath({56.3,54.7,53.6,52.4,51.7,50.6,49.2,48.6,47,45.8,45,44,43.2,42.4,41.5,40,39.2,38,37.3,36.4,35.6,34.7,33.3,32.4,31.3,30.5,29.6,28.8,27.6,26.8,26,25,24.2,23.6,23,22.2,21,19.7,18.8,17.4,16.8,15.7,15,14.8,14,13.4,11.7,11.4,10.6,10,9.2,8.6,7.4,7}, {17,17,17,17.5,18,19.3,20.4,21,21,21,21,21,21,21,21,21,21.3,21.6,21.9,21.9,21.9,21.9,22,22,22.4,22.4,22.4,22.4,22.4,22.4,22.7,22.7,22.7,21.8,21.3,20.4,19.3,18.7,18.2,17.3,16.7,16.2,15.3,14.5,13.6,13,11.6,10.8,10.2,9.7,9,8.2,7.7,7});
    wait (1, sec);
    TopIntake.spin(reverse, 100, pct);
    BottomIntake.spin(reverse, 100, pct);
    ReversedIntake.spin(reverse, 100, pct);
    wait (3, sec);
    DescorePiston.set(true);
    TopIntake.stop();
    BottomIntake.stop();
    ReversedIntake.stop();
    curveToPosition(40, 48.3);
    driveToPosition(58.7, 48.3, fwd);
    TopIntake.spin(fwd, 10, pct);
    BottomIntake.spin(fwd, 100, pct);
    ReversedIntake.spin(fwd, 100, pct);
    wait (1, sec);
    DescorePiston.set(false);
    IntakePiston.set(true);
    driveIn(-5);
    turnToHeading(270);
    driveIn(16);
    TopIntake.spin(fwd, 100, pct);
    BottomIntake.spin(fwd, 100, pct);
    ReversedIntake.spin(fwd, 100, pct);
}