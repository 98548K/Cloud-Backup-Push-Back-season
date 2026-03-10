#include "vex.h"

int quadrant = 0;
bool isCalibrated = false;
bool ranOnce = false;
const char*  auton = "[NULL]";


//Quadrant 1: Top right quadrant.
//Quadrant 2: Bottom right quadrant.
//quadrant 3: Top left quadrant.
//Quadrant 4: Bottom left quadrant.

double beginHeading;
double beginX;
double beginY;


void field() {
  //This is the field:
  Brain.Screen.drawImageFromFile("Empty_Field.png", 0, 0);
}




void selection() {
  //This is the selection menu:
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.drawRectangle(240, 0, 250, 50);
  Brain.Screen.drawRectangle(240, 50, 250, 50);
  Brain.Screen.drawRectangle(240, 100, 250, 50);
  Brain.Screen.drawRectangle(240, 150, 250, 50);
  Brain.Screen.drawRectangle(240, 200, 250, 50);
}

void graphics() {
  Brain.Screen.clearScreen();
  field();
  selection();
}


void clear_menu() {
  Brain.Screen.printAt(251, 90, "                       ");
  Brain.Screen.printAt(251, 140, "                      ");
  Brain.Screen.printAt(251, 190, "                      ");
  Brain.Screen.printAt(251, 235, "                      ");
}

void displayOptions(const char* label1, const char* label2, const char* label3, const char* label4) {
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor(green);
  Brain.Screen.printAt(241, 90, label1);
  Brain.Screen.printAt(241, 140, label2);
  Brain.Screen.printAt(241, 190, label3);
  Brain.Screen.printAt(241, 235, label4);
}

const char* row = "[NULL]";
std::vector<const char*> autoVector;

const char* setAuton(const char* row1, const char* row2, const char* row3, const char* row4) {
  if (Brain.Screen.xPosition() > 240 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
    row = row1;
  }
  else if (Brain.Screen.xPosition() > 240 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 150) {
    row = row2;
  }
  else if (Brain.Screen.xPosition() > 240 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 200) {
    row = row3;
  }
  else if (Brain.Screen.xPosition() > 240 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 250) {
    row = row4;
  }
  return row;
}

double externHeading;

//Each list is ordered as follows: inertial heading, X, Y
double startHeading(double row1, double row2, double row3, double row4) {
  if (auton == autoVector[0]) {
    externHeading = row1;
  }
  else if (auton == autoVector[1]) {
    externHeading = row2;
  }
  else if (auton == autoVector[2]) {
    externHeading = row3;
  }
  else if (auton == autoVector[3]) {
    externHeading = row4;
  }
  return externHeading;
}

double externX;

double startX(double row1, double row2, double row3, double row4) {
  if (auton == autoVector[0]) {
    externX = row1;
  }
  else if (auton == autoVector[1]) {
    externX = row2;
  }
  else if (auton == autoVector[2]) {
    externX = row3;
  }
  else if (auton == autoVector[3]) {
    externX = row4;
  }
  return externX;
}

double externY;

double startY(double row1, double row2, double row3, double row4) {
  if (auton == autoVector[0]) {
    externY = row1;
  }
  else if (auton == autoVector[1]) {
    externY = row2;
  }
  else if (auton == autoVector[2]) {
    externY = row3;
  }
  else if (auton == autoVector[3]) {
    externY = row4;
  }
  return externY;
}


void touch() {
  while(true) {
    isCalibrated = false;
    Brain.Screen.setFillColor(black);
    //Side menu touch screen code:
    if (Brain.Screen.xPosition() < 240 && Brain.Screen.xPosition() > 125 && Brain.Screen.yPosition() < 120) {
      clear_menu();
      quadrant = 1;
    }
    else if (Brain.Screen.xPosition() < 240 && Brain.Screen.xPosition() > 125 && Brain.Screen.yPosition() > 120) {
      clear_menu();
      quadrant = 2;
    }
    else if (Brain.Screen.xPosition() > 0 && Brain.Screen.xPosition() < 125 && Brain.Screen.yPosition() > 120) {
      clear_menu();
      quadrant = 3;
    }
    else if (Brain.Screen.xPosition() > 0 && Brain.Screen.xPosition() < 125 && Brain.Screen.yPosition() < 120) {
      clear_menu();
      quadrant = 4;
    }
    
    if (auton == "[NULL]") {
      auto_run();
    }

    if (quadrant == 0) {
      clear_menu();
      Brain.Screen.setFont(monoXL);
      Brain.Screen.setPenColor(green);
      Brain.Screen.printAt(241, 90, "Skills");
      Brain.Screen.printAt(241, 140, "Calibrate");
      Brain.Screen.printAt(241, 190, "Other Red");
      Brain.Screen.printAt(241, 235, "Other Blue");
      if (Brain.Screen.xPosition() > 240 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
        auton = "Skills";
        beginHeading = skills_.selectedHeading();
        beginX = skills_.selectedX();
        beginY = skills_.selectedY();
      }
      else if (Brain.Screen.xPosition() > 240 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 150) {
        isCalibrated = true;
      }
      else if (Brain.Screen.xPosition() > 240 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 200) {
        auton = "Other red";
      }
      else if (Brain.Screen.xPosition() > 240 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 250) {
        auton = "Other blue";
      }
    }

    else if (quadrant == 1) {
      autoVector = {"Right", "Right 7", "Right Odom", "Empty"};
      displayOptions(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      auton = setAuton(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      //Depending on the name of the auton configures starting heading
      beginHeading = startHeading(
        linkedAutons.at(autoVector[0]).selectedHeading(), 
        linkedAutons.at(autoVector[1]).selectedHeading(), 
        linkedAutons.at(autoVector[2]).selectedHeading(), 
        linkedAutons.at(autoVector[4]).selectedHeading()
      );
      //Depending on the name of the auton configures starting x
      beginX = startX(
        linkedAutons.at(autoVector[0]).selectedX(), 
        linkedAutons.at(autoVector[1]).selectedX(), 
        linkedAutons.at(autoVector[2]).selectedX(), 
        linkedAutons.at(autoVector[4]).selectedX()
      );
      //Depending on the name of the auton configures starting y
      beginY = startY(
        linkedAutons.at(autoVector[0]).selectedY(), 
        linkedAutons.at(autoVector[1]).selectedY(), 
        linkedAutons.at(autoVector[2]).selectedY(), 
        linkedAutons.at(autoVector[4]).selectedY()
      );
    }

    else if (quadrant == 2) {
      autoVector = {"Left", "Empty", "Empty", "Empty"};
      displayOptions(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      auton = setAuton(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      //Depending on the name of the auton configures starting heading
      beginHeading = startHeading(
        linkedAutons.at(autoVector[0]).selectedHeading(), 
        linkedAutons.at(autoVector[1]).selectedHeading(), 
        linkedAutons.at(autoVector[2]).selectedHeading(), 
        linkedAutons.at(autoVector[4]).selectedHeading()
      );
      //Depending on the name of the auton configures starting x
      beginX = startX(
        linkedAutons.at(autoVector[0]).selectedX(), 
        linkedAutons.at(autoVector[1]).selectedX(), 
        linkedAutons.at(autoVector[2]).selectedX(), 
        linkedAutons.at(autoVector[4]).selectedX()
      );
      //Depending on the name of the auton configures starting y
      beginY = startY(
        linkedAutons.at(autoVector[0]).selectedY(), 
        linkedAutons.at(autoVector[1]).selectedY(), 
        linkedAutons.at(autoVector[2]).selectedY(), 
        linkedAutons.at(autoVector[4]).selectedY()
      );
    }
    else if (quadrant == 3) {
      autoVector = {"Right", "Right 7", "Right Odom", "Empty"};
      displayOptions(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      auton = setAuton(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      //Depending on the name of the auton configures starting heading
      beginHeading = startHeading(
        linkedAutons.at(autoVector[0]).selectedHeading(), 
        linkedAutons.at(autoVector[1]).selectedHeading(), 
        linkedAutons.at(autoVector[2]).selectedHeading(), 
        linkedAutons.at(autoVector[4]).selectedHeading()
      );
      //Depending on the name of the auton configures starting x
      beginX = startX(
        linkedAutons.at(autoVector[0]).selectedX(), 
        linkedAutons.at(autoVector[1]).selectedX(), 
        linkedAutons.at(autoVector[2]).selectedX(), 
        linkedAutons.at(autoVector[4]).selectedX()
      );
      //Depending on the name of the auton configures starting y
      beginY = startY(
        linkedAutons.at(autoVector[0]).selectedY(), 
        linkedAutons.at(autoVector[1]).selectedY(), 
        linkedAutons.at(autoVector[2]).selectedY(), 
        linkedAutons.at(autoVector[4]).selectedY()
      );
    }
    else if (quadrant == 4) {
      autoVector = {"Left", "Empty", "Empty", "Empty"};
      displayOptions(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      auton = setAuton(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      //Depending on the name of the auton configures starting heading
      beginHeading = startHeading(
        linkedAutons.at(autoVector[0]).selectedHeading(), 
        linkedAutons.at(autoVector[1]).selectedHeading(), 
        linkedAutons.at(autoVector[2]).selectedHeading(), 
        linkedAutons.at(autoVector[4]).selectedHeading()
      );
      //Depending on the name of the auton configures starting x
      beginX = startX(
        linkedAutons.at(autoVector[0]).selectedX(), 
        linkedAutons.at(autoVector[1]).selectedX(), 
        linkedAutons.at(autoVector[2]).selectedX(), 
        linkedAutons.at(autoVector[4]).selectedX()
      );
      //Depending on the name of the auton configures starting y
      beginY = startY(
        linkedAutons.at(autoVector[0]).selectedY(), 
        linkedAutons.at(autoVector[1]).selectedY(), 
        linkedAutons.at(autoVector[2]).selectedY(), 
        linkedAutons.at(autoVector[4]).selectedY()
      );
    }

    

    //Calibrates the robot if the robot has moved to a certain extent
    if (!enabledComp()) {
      if (Inertial1.isCalibrating()) {
        Inertial1.setHeading(beginHeading, deg);
        setDrivePosition(beginX, beginY);
      }
      else if (std::round(Inertial1.heading(deg)) != validateHeading(beginHeading) && std::round(Inertial1.heading(deg)) != validateHeading(beginHeading - 1) && std::round(Inertial1.heading(deg)) != validateHeading(beginHeading + 1) && std::round(Inertial1.heading(deg)) != validateHeading(beginHeading - 2) && std::round(Inertial1.heading(deg)) != validateHeading(beginHeading + 2)) {
        Inertial1.calibrate();
      }
    }

    Brain.Screen.render();

    Brain.Screen.setFont(monoXL);
    Brain.Screen.setPenColor(green);
    Brain.Screen.setFillColor(black);
    Brain.Screen.printAt(241, 40, "                ");
    Brain.Screen.printAt(241, 40, auton);
    if (isCalibrated && !ranOnce) {
      Inertial1.calibrate();
      Brain.Screen.printAt(241, 140, "3           ");
      wait (1, sec);
      Brain.Screen.printAt(241, 140, "2           ");
      wait (1, sec);
      Brain.Screen.printAt(241, 140, "1           ");
      wait (1, sec);
      Brain.Screen.printAt(241, 140, "Calibrated");
      //
      /*Brain.Screen.drawImageFromFile("Image.png", 0, 0);
      wait (3, sec);
      Brain.Screen.clearScreen();
      graphics();*/
      //
      isCalibrated = false;
      ranOnce = true;
    }
    wait(20, msec);
    
  }
}
void selectable() {
  graphics();
  touch();
}