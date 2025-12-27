#include "vex.h"

int quadrant = 0;
bool isCalibrated = false;
bool ranOnce = false;
const char*  auton = "[NULL]";


//Quadrant 1: Top right quadrant.
//Quadrant 2: Bottom right quadrant.
//quadrant 3: Top left quadrant.
//Quadrant 4: Bottom left quadrant.


void field() {
  //This is the field:
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0, 0, 250, 240);
}




void selection() {
  //This is the selection menu:
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(monoXL);
  Brain.Screen.drawRectangle(250, 0, 250, 50);
  Brain.Screen.drawRectangle(250, 50, 250, 50);
  Brain.Screen.drawRectangle(250, 100, 250, 50);
  Brain.Screen.drawRectangle(250, 150, 250, 50);
  Brain.Screen.drawRectangle(250, 200, 250, 50);
}




void field_stripes() {
  //This is the field stripes:
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(white);
  //Left middle line:
  Brain.Screen.drawLine(123, 0, 123, 240);
  //Right middle line:
  Brain.Screen.drawLine(127, 0, 127, 240);
}




void end_zones() {
  //Red end zone:
  Brain.Screen.setPenColor(red);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0, 95, 50, 50);
  //Blue end zone:
  Brain.Screen.setPenColor(blue);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(200, 95, 50, 50);
}

void goals() {
  //Top left to bottom right in the middle goal:
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.drawLine(115, 100, 145, 130);
  Brain.Screen.drawLine(105, 110, 135, 140);
  Brain.Screen.drawLine(115, 100, 105, 110);
  Brain.Screen.drawLine(145, 130, 135, 140);
  //Top right to bottom left in the middle goal:
  Brain.Screen.drawLine(145, 110, 115, 140);
  Brain.Screen.drawLine(135, 100, 105, 130);
  Brain.Screen.drawLine(145, 110, 135, 100);
  Brain.Screen.drawLine(115, 140, 105, 130);
  //Top middle goal:
  Brain.Screen.drawRectangle(85, 35, 80, 15);
  //Bottom middle goal:
  Brain.Screen.drawRectangle(85, 195, 80, 15);
}


//Weird formatting because that's just how cool we are.
void block_things() {
  //Red blocks:
  Brain.Screen.setFillColor(red);
  Brain.Screen.setPenColor(red);
    //End zone:
  Brain.Screen.drawCircle(205, 105, 4);
  Brain.Screen.drawCircle(205, 115, 4);
  Brain.Screen.drawCircle(205, 125, 4);
  Brain.Screen.drawCircle(205, 135, 4);
    //Surrounding goals:
      //Top:
  Brain.Screen.drawCircle(85, 80, 4);
  Brain.Screen.drawCircle(95, 80, 4);
  Brain.Screen.drawCircle(85, 90, 4);
      //Bottom:
  Brain.Screen.drawCircle(85, 160, 4);
  Brain.Screen.drawCircle(95, 160, 4);
  Brain.Screen.drawCircle(85, 150, 4);
    //Next to walls:
      //Top:
  Brain.Screen.drawCircle(190, 5, 4);
  Brain.Screen.drawCircle(200, 5, 4);
      //Bottom:
  Brain.Screen.drawCircle(190, 234, 4);
  Brain.Screen.drawCircle(200, 234, 4);
    //Under goals:
  Brain.Screen.drawCircle(120, 42, 4);
  Brain.Screen.drawCircle(110, 42, 4);
  Brain.Screen.drawCircle(120, 202, 4);
  Brain.Screen.drawCircle(110, 202, 4);


  //Blue blocks:
  Brain.Screen.setFillColor(blue);
  Brain.Screen.setPenColor(blue);
    //End zone:
  Brain.Screen.drawCircle(44, 105, 4);
  Brain.Screen.drawCircle(44, 115, 4);
  Brain.Screen.drawCircle(44, 125, 4);
  Brain.Screen.drawCircle(44, 135, 4);
    //Surrounding goals:
      //Top:
  Brain.Screen.drawCircle(165, 80, 4);
  Brain.Screen.drawCircle(155, 80, 4);
  Brain.Screen.drawCircle(165, 90, 4);
      //Bottom:
  Brain.Screen.drawCircle(165, 160, 4);
  Brain.Screen.drawCircle(155, 160, 4);
  Brain.Screen.drawCircle(165, 150, 4);
    //Next to walls:
      //Top:
  Brain.Screen.drawCircle(50, 5, 4);
  Brain.Screen.drawCircle(60, 5, 4);
      //Bottom:
  Brain.Screen.drawCircle(50, 234, 4);
  Brain.Screen.drawCircle(60, 234, 4);
    //Under goals:
  Brain.Screen.drawCircle(130, 42, 4);
  Brain.Screen.drawCircle(140, 42, 4);
  Brain.Screen.drawCircle(130, 202, 4);
  Brain.Screen.drawCircle(140, 202, 4);
}




void loader() {
  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(orange);
  //Creates the hollowed loader effect:
  Brain.Screen.drawCircle(7, 42, 7);
  Brain.Screen.drawCircle(7, 202, 7);
  Brain.Screen.drawCircle(242, 42, 7);
  Brain.Screen.drawCircle(242, 202, 7);
  //Red alliance side:
  Brain.Screen.setFillColor(blue);
  Brain.Screen.setPenColor(blue);
  Brain.Screen.drawCircle(7, 42, 4);
  Brain.Screen.drawCircle(7, 202, 4);
  //Blue alliance side:
  Brain.Screen.setFillColor(red);
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawCircle(242, 42, 4);
  Brain.Screen.drawCircle(242, 202, 4);
}




//Keep layering in mind:
void graphics() {
  Brain.Screen.clearScreen();
  field();
  field_stripes();
  selection();
  end_zones();
  goals();
  loader();
  block_things();
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
  Brain.Screen.printAt(251, 90, label1);
  Brain.Screen.printAt(251, 140, label2);
  Brain.Screen.printAt(251, 190, label3);
  Brain.Screen.printAt(251, 235, label4);
}

const char* row = "[NULL]";
std::vector<const char*> autoVector;

const char* setAuton(const char* row1, const char* row2, const char* row3, const char* row4) {
  if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
    row = row1;
  }
  else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 150) {
    row = row2;
  }
  else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 200) {
    row = row3;
  }
  else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 250) {
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
    if (Brain.Screen.xPosition() < 250 && Brain.Screen.xPosition() > 125 && Brain.Screen.yPosition() < 120) {
      clear_menu();
      quadrant = 1;
    }
    else if (Brain.Screen.xPosition() < 250 && Brain.Screen.xPosition() > 125 && Brain.Screen.yPosition() > 120) {
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

    if (quadrant == 0) {
      clear_menu();
      Brain.Screen.setFont(monoXL);
      Brain.Screen.setPenColor(green);
      Brain.Screen.printAt(251, 90, "Skills");
      Brain.Screen.printAt(251, 140, "Calibrate");
      Brain.Screen.printAt(251, 190, "Other Red");
      Brain.Screen.printAt(251, 235, "Other Blue");
      if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
        auton = "Skills";
        beginHeading = 327;
        beginX = 40;
        beginY = 23.5;
      }
      else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 150) {
        isCalibrated = true;
      }
      else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 200) {
        auton = "Other red";
      }
      else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 250) {
        auton = "Other blue";
      }
    }

    else if (quadrant == 1) {
      autoVector = {"Right", "Empty2", "Empty3", "Empty4"};
      displayOptions(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      auton = setAuton(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      beginHeading = startHeading(277, 0, 0, 0);
      beginX = startX(55, 0, 0, 0);
      beginY = startY(22, 0, 0, 0);
    }




    else if (quadrant == 2) {
      autoVector = {"Left", "Empty6", "Empty7", "Empty8"};
      displayOptions(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      auton = setAuton(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      beginHeading = startHeading(263, 0, 0, 0);
      beginX = startX(55, 0, 0, 0);
      beginY = startY(-22, 0, 0, 0);
    }
     
    else if (quadrant == 3) {
      autoVector = {"Right", "Empty10", "Empty11", "Empty12"};
      displayOptions(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      auton = setAuton(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      beginHeading = startHeading(277, 0, 0, 0);
      beginX = startX(55, 0, 0, 0);
      beginY = startY(22, 0, 0, 0);
    }




    else if (quadrant == 4) {
      autoVector = {"Left", "Empty14", "Empty15", "Empty16"};
      displayOptions(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      auton = setAuton(autoVector[0], autoVector[1], autoVector[2], autoVector[3]);
      beginHeading = startHeading(263, 0, 0, 0);
      beginX = startX(55, 0, 0, 0);
      beginY = startY(-22, 0, 0, 0);
    }

    
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
    Brain.Screen.printAt(251, 40, "                ");
    Brain.Screen.printAt(251, 40, auton);
    if (isCalibrated && !ranOnce) {
      Inertial1.calibrate();
      Brain.Screen.printAt(251, 140, "3           ");
      wait (1, sec);
      Brain.Screen.printAt(251, 140, "2           ");
      wait (1, sec);
      Brain.Screen.printAt(251, 140, "1           ");
      wait (1, sec);
      Brain.Screen.printAt(251, 140, "Calibrated");
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