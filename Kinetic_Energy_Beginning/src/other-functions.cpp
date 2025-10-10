#include "vex.h"

//Coding motivation here: https://www.youtube.com/watch?v=ruAlvlacEuM

int sortColorRed() {
  while (true) {
    if (BorderControl.hue() >= 300 && BorderControl.hue() <= 400) {
      BruteForce.set(true);
      wait (20, msec);
      BruteForce.set(false);
    }
  }
  return 0;
}

int sortColorBlue() {
  while (true) {
    if (BorderControl.hue() >= 145 && BorderControl.hue() <= 215) {
      BruteForce.set(true);
      wait (20, msec);
      BruteForce.set(false);
    }
  }
  return 0;
}

task colorSortingRed = task(sortColorRed);
task colorSortingBlue = task(sortColorBlue);