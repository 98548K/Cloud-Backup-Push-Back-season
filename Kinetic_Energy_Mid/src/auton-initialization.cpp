#include "vex.h"

initialize_auto::initialize_auto(double GlobalX, double GlobalY, double GlobalHeading) {
    this->globalX = GlobalX;
    this->globalY = GlobalY;
    this->globalHeading = GlobalHeading;
}

double initialize_auto::selectedX() {
    return globalX;
}

double initialize_auto::selectedY() {
    return globalY;
}

double initialize_auto::selectedHeading() {
    return globalHeading;
}

//Declare autons here (Xpos, Ypos, Heading)
initialize_auto skills_ = initialize_auto(-55, -24, 149);
initialize_auto right_ = initialize_auto(48, 6, 295);
initialize_auto left_ = initialize_auto(48, -6, 243);
initialize_auto right_odom_ = initialize_auto(-61.4, -25.5, 156.7);
initialize_auto empty_ = initialize_auto(0, 0, 0);

//When an auton is not selected, it will configure this stuff instead
void auto_run() {
    beginHeading = skills_.selectedHeading();
    beginX = skills_.selectedX();
    beginY = skills_.selectedY();
}

//Initialize for selectable auton
std::map<const char*, initialize_auto> linkedAutons = {
    {"Right", right_},
    {"Left", left_},
    {"Skills", skills_},
    {"Right Odom", right_odom_},
    {"Empty", empty_}
};