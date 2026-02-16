#include "vex.h"

//Coding motivation here: https://www.youtube.com/watch?v=ruAlvlacEuM
double deployRange;
double loggedPosition;


int sortColorRed() {
  while (true) {
    if (BorderControl.hue() >= 10 && BorderControl.hue() <= 350 && BorderControl.objectDetectThreshold(50)) {
      BruteForce.set(false);
    }
    else {
      BruteForce.set(true);
      wait (500, msec);
    }
  }
  return 0;
}

int sortColorBlue() {
  while (true) {
    if (BorderControl.hue() >= 145 && BorderControl.hue() <= 215 && BorderControl.objectDetectThreshold(50)) {
      BruteForce.set(false);
    }
    else {
      BruteForce.set(true);
      wait (500, msec);
    }
  }
  return 0;
}

task colorSortingRed = task(sortColorRed);
task colorSortingBlue = task(sortColorBlue);