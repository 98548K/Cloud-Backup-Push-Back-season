#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <cmath>
#include <iostream>

#include "v5.h"
#include "v5_vcs.h"

#include "auton-selector.h"
#include "autonomous.h"
#include "autons.h"
#include "odometry.h"
#include "other-functions.h"
#include "PID.h"
#include "pre-auton.h"
#include "pure-pursuit.h"
#include "robot-config.h"
#include "user-control.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)