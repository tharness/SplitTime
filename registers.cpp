#include "registers.h"

int oldRockX = 0;
int oldRockY = 0;
int rockX = 0;
int rockY = 0;
int rockXBound = 15;
int rockYBound = 1;

int currentPlayer = 0;
int currentRockRotation = 0;

unsigned long stopwatchStartTime = 0;
float split = 0.0;