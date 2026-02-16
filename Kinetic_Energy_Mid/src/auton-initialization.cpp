#include "vex.h"



initialize_auto::initialize_auto(double GlobalX, double GlobalY, double GlobalHeading) {
    globalX = GlobalX;
    globalY = GlobalY;
    globalHeading = GlobalHeading;
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

initialize_auto skills_ = initialize_auto(-55, -24, 149);
initialize_auto right_ = initialize_auto(48, 6, 295);
initialize_auto left_ = initialize_auto(48, -6, 295);