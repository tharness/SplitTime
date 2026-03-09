#ifndef CALCS_H
#define CALCS_H

#include "data.h"

float getPlayerSplitForZone(int player, int zone);
// -1 for zone prediction below recorded data, 0 for within, +1 for zone prediction above recorded data
int getPlayerSplitStatus(int player, float split);
// -1 for no data
int getZoneforPlayerSplit(int player, float split);

#endif // CALCS_H