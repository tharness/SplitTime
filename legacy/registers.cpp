#include "registers.h"

int currentPlayer = 0;
// 1 indicates shot data should be recorded, 0 not recorded
int recordShotData = 1;

unsigned long stopwatchStartTime = 0;
float split = 0.0;
// -1 indicates no data available
int zone = -1;
// -1 indicates lower than recorded data, , 1 greater, 0 real prediction
int zoneFlag = 0;
int zoneCursor = 0;