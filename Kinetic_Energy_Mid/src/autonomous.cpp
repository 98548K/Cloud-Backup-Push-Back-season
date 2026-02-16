#include "vex.h"

void autonomous(void) {
    setDriveConstants(2.5, 0.9, 2.8);
    setTurnConstants(0.36,0.16,3.8);
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
    else if (auton == "Other blue") {
        
    }
    else {
        Skills();
        //turnToHeading(90);
        //Drivetrain.driveFor(2,inches);
    }
}