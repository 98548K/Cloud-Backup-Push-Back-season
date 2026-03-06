#include "vex.h"

void autonomous(void) {
    setDriveConstants(2.8, 0.0, 0);//setDriveConstants(2.8, 0.0011, 0);
    setTurnConstants(0.33, 0.0, 0.79);//setTurnConstants(0.33, 0.000000001, 0.79);
    if (auton == "Skills") {
        Skills();
    }
    else if (auton == "Left") {
        Left();
    }
    else if (auton == "Right") {
        Right();
    }
    else if (auton == "Right") {
        Right();
    }
    else if (auton == "Left") {
        Left();
    }
    else if (auton == "Right 7") {
        Right_7_Block();
    }
    else if (auton == "Right Odom") {
        Odom_Right();
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
    else if (auton == "Other blue") {
        
    }
    else {
        Skills();
    }
}