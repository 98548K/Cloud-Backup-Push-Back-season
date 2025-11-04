#include "vex.h"

//Coding motivation here: https://www.youtube.com/watch?v=ruAlvlacEuM

int sortColorRed() {
  while (true) {
    if (BorderControl.hue() >= 10 && BorderControl.hue() <= 350 && BorderControl.objectDetectThreshold(127)) {
      BruteForce.set(false);
      wait (10, msec);
      BruteForce.set(true);
    }
  }
  return 0;
}

int sortColorBlue() {
  while (true) {
    if (BorderControl.hue() >= 145 && BorderControl.hue() <= 215) {
      BruteForce.set(false);
      wait (10, msec);
      BruteForce.set(true);
    }
  }
  return 0;
}

task colorSortingRed = task(sortColorRed);
task colorSortingBlue = task(sortColorBlue);