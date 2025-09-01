#include "vex.h"


void autonomous(void) {
    if (auton == "Skills") {
        
    }
    else if (auton == "Blue 4 ring") {
        
    }
    else if (auton == "Blue 5 ring") {
        
    }
    else if (auton == "Bsig win pt") {
        
    }
    else if (auton == "Blue 6 ring") {
        
    }
    else if (auton == "Blue 2 ring") {
        
    }
    else if (auton == "Blue 3 ring") {
        
    }
    else if (auton == "Blue win pt") {
        
    }
    else if (auton == "Blue goal") {
        
    }
    else if (auton == "Red 4 ring") {
        
    }
    else if (auton == "Red 5 ring") {
        
    }
    else if (auton == "Rsig win pt") {
        
    }
    else if (auton == "Red 6 ring") {
        
    }
    else if (auton == "Red 2 ring") {
        
    }
    else if (auton == "Red 3 ring") {
        
    }
    else if (auton == "Red win pt") {
        
    }
    else if (auton == "Red goal") {
        
    }
    else if (auton == "Other red") {
        
    }
    else if (auton == "Other_blue") {
        
    }
    else {
        frontTracking.setPosition(0, turns);
        sideTracking.setPosition(0, turns);
        LeftDriveSmart.setPosition(0, turns);
        RightDriveSmart.setPosition(0, turns);
        setDrivePosition(-15.5, 33.3, 260.5376871539586);
        wait (6, sec);
        tracePath({-19.8,-20.5,-21.6,-26,-26.8,-27,-28,-28.6,-29.3,-31.5,-32.3,-34,-35.2,-36,-37.4,-37.8,-37.8,-38.5,-39,-39.2,-39.2,-40,-40,-40.3,-40.7,-40.7,-41,-41,-41,-41,-41,-41,-40.7,-40.3,-40,-39.2,-39,-39,-38.5,-38,-37.8,-37.4,-36.3,-35.2,-34,-33,-32,-31,-29,-26.8,-26,-24.6,-23.5,-22.7,-21.6,-19.4,-17.6,-16.5,-15.4,-14,-12,-11,-10,-9,-5,-3.7,-3,0.7,3.7,7,8.8,10.3,11.4,12.5,13.6,15.4,17.6,18.7,19.8,21,22,22.7,23.5,24}, {32,32.4,32.4,31.6,31,30,29.8,28.7,27.2,24.7,24,21.7,20.3,18.4,15.5,14.8,13.7,12.6,11.5,10.4,9.6,8,6.7,5.2,3.8,2.3,1.2,0,-1.7,-3,-4.3,-8.3,-10.5,-11.6,-12.4,-14,-15.3,-16.4,-19,-22,-23.7,-24.5,-24.5,-25,-25,-25,-25,-25.2,-27.4,-29,-29.6,-30.3,-30.7,-30.7,-30.7,-31,-31,-31,-31,-31.4,-32,-32,-32,-32,-32.5,-33,-33.3,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-34.7,-34.4,-34,-33.3});
        //curveToPosition(30, 0);
        //curveToPosition(0, 30);
        //curveToPosition(-30, 0);
        //curveToPosition(0, -30);
    }
}