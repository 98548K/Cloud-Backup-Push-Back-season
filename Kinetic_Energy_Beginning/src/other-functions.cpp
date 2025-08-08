#include "vex.h"

//Coding motivation here: https://www.youtube.com/watch?v=ruAlvlacEuM

int colorSortRed() {
    while (true) {
        red_detected();
        wait (20, msec);
    }
}




int colorSortBlue() {
    while (true) {
        blue_detected();
        wait (20, msec);
    }
}


//Color sort function
void blue_detected() {
    if (ringOptical.hue() > 110 && ringOptical.hue() < 120) {
        colorSort.set(true);
        wait (.02, sec);
        colorSort.set(false);
   }
   else if (ringOptical.hue() > 110 && ringOptical.hue() < 120) {
        colorSort.set(true);
        wait (.02, sec);
        colorSort.set(false);
   }
}

void red_detected() {
    if (ringOptical.hue() > 15 && ringOptical.hue() < 25) {
        colorSort.set(false);
        wait (.02, sec);
        colorSort.set(true);
   }
   else if (ringOptical.hue() > 15 && ringOptical.hue() < 25) {
        colorSort.set(false);
        wait (.02, sec);
        colorSort.set(true);
   }
}

