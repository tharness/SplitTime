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
// -1 indicates no data available
int zone = -1;
// -1 indicates lower than recorded data, , 1 greater, 0 real prediction
int zoneFlag = 0;
int zoneCursor = 0;