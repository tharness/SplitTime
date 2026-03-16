#ifndef REGISTERS_H
#define REGISTERS_H

extern int currentPlayer;
// 1 indicates shot data should be recorded, 0 not recorded
extern int recordShotData;

extern unsigned long stopwatchStartTime;
extern float split;
// -1 indicates no data available
extern int zone;
// -1 indicates lower than recorded data, , 1 greater, 0 real prediction
extern int zoneFlag;
extern int zoneCursor;

#endif // REGISTERS_H