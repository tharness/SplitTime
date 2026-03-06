#ifndef REGISTERS_H
#define REGISTERS_H

extern int oldRockX;
extern int oldRockY;
extern int rockX;
extern int rockY;
extern int rockXBound;
extern int rockYBound;

extern int currentPlayer;
extern int currentRockRotation;

extern unsigned long stopwatchStartTime;
extern float split;
extern int zonePrediction;
// -1 indicates lower than recorded data, , 1 greater, 0 real prediction
extern int zoneFlag;

#endif // REGISTERS_H