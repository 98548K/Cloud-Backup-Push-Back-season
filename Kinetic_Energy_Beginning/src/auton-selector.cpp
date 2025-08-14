#include "vex.h"
int quadrant = 0;
bool isCalibrated = false;
bool ranOnce = false;
const char*  auton = "[NULL]";


void quadrant0() {
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor(green);
  Brain.Screen.printAt(251, 90, "Skills       ");
  Brain.Screen.printAt(251, 140, "Calibrate   ");
  Brain.Screen.printAt(251, 190, "Other red   ");
  Brain.Screen.printAt(251, 235, "Other blue  ");
}

void quadrant1() {
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor(green);
  Brain.Screen.printAt(251, 90, "Empty1");
  Brain.Screen.printAt(251, 140, "Empty2");
  Brain.Screen.printAt(251, 190, "Empty3");
  Brain.Screen.printAt(251, 235, "Empty4");
}


void quadrant2() {
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor(green);
  Brain.Screen.printAt(251, 90, "Empty5");
  Brain.Screen.printAt(251, 140, "Empty6");
  Brain.Screen.printAt(251, 190, "Empty7");
  Brain.Screen.printAt(251, 235, "Empty8");
}


void quadrant3() {
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor(green);
  Brain.Screen.printAt(251, 90, "Empty9");
  Brain.Screen.printAt(251, 140, "Empty10");
  Brain.Screen.printAt(251, 190, "Empty11");
  Brain.Screen.printAt(251, 235, "Empty12");
}


void quadrant4() {
  Brain.Screen.setFont(monoXL);
  Brain.Screen.setPenColor(green);
  Brain.Screen.printAt(251, 90, "Empty13");
  Brain.Screen.printAt(251, 140, "Empty14");
  Brain.Screen.printAt(251, 190, "Empty15");
  Brain.Screen.printAt(251, 235, "Empty16");
}


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


//Keep layering in mind.
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


void touch() {
  while(true) {
    isCalibrated = false;
    Brain.Screen.setFillColor(black);
      if (Brain.Screen.xPosition() < 250 && Brain.Screen.xPosition() > 125 && Brain.Screen.yPosition() < 120) {
        Brain.Screen.printAt(251, 90, "                       ");
        Brain.Screen.printAt(251, 140, "                      ");
        Brain.Screen.printAt(251, 190, "                      ");
        Brain.Screen.printAt(251, 235, "                      ");
        quadrant1();
        quadrant = 1;
      }
      else if (Brain.Screen.xPosition() < 250 && Brain.Screen.xPosition() > 125 && Brain.Screen.yPosition() > 120) {
        Brain.Screen.printAt(251, 90, "                       ");
        Brain.Screen.printAt(251, 140, "                      ");
        Brain.Screen.printAt(251, 190, "                      ");
        Brain.Screen.printAt(251, 235, "                      ");
        quadrant2();
        quadrant = 2;
      }
      else if (Brain.Screen.xPosition() > 0 && Brain.Screen.xPosition() < 125 && Brain.Screen.yPosition() > 120) {
        Brain.Screen.printAt(251, 90, "                       ");
        Brain.Screen.printAt(251, 140, "                      ");
        Brain.Screen.printAt(251, 190, "                      ");
        Brain.Screen.printAt(251, 235, "                      ");
        quadrant3();
        quadrant = 3;
      }
      else if (Brain.Screen.xPosition() > 0 && Brain.Screen.xPosition() < 125 && Brain.Screen.yPosition() < 120) {
        Brain.Screen.printAt(251, 90, "                       ");
        Brain.Screen.printAt(251, 140, "                      ");
        Brain.Screen.printAt(251, 190, "                      ");
        Brain.Screen.printAt(251, 235, "                      ");
        quadrant4();
        quadrant = 4;
      }
      //Side menu touch screen code:
      if (quadrant == 0) {
        quadrant0();
        if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
          auton = "Skills";
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
        quadrant1();
        if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
          auton = "Empty1";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 150) {
          auton = "Empty2";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 200) {
          auton = "Empty3";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 250) {
          auton = "Empty4";
        }

      }


      else if (quadrant == 2) {
        quadrant2();
        if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
          auton = "Empty5";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 150) {
          auton = "Empty6";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 200) {
          auton = "Empty7";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 250) {
          auton = "Empty8";
        }

      }
     
      else if (quadrant == 3) {
        quadrant3();
        if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
          auton = "Empty9";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 150) {
          auton = "Empty10";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 200) {
          auton = "Empty11";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 250) {
          auton = "Empty12";
        }

      }


      else if (quadrant == 4) {
        quadrant4();
        if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 50 && Brain.Screen.yPosition() < 100) {
          auton = "Empty13";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 150) {
          auton = "Empty14";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 200) {
          auton = "Empty15";
        }
        else if (Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() < 250) {
          auton = "Empty16";
        }

      }

    Brain.Screen.setFont(monoXL);
    Brain.Screen.setPenColor(green);
    Brain.Screen.setFillColor(black);
    Brain.Screen.printAt(251, 40, "                ");
    Brain.Screen.printAt(251, 40, auton);
    if (isCalibrated && !ranOnce) {
      //Try this next time I have a brain in my possesion:
      //Brain.Screen.setTouchEventCallback(nullptr);
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