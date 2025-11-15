#include "vex.h"


void autonomous(void) {
    if (auton == "Skills") {
        Bad_Skills();
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
    else if (auton == "Other_blue") {
        
    }
    else {
        //Left();
        //Right();
        //Bad_Skills();
        //curveToPosition(24, 24);
        Skills();
    }
}