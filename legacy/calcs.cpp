#include "calcs.h"
#include <math.h>

float getPlayerSplitForZone(int player, int zone) {
  int count = getShotCountForPlayer(player);
  shot* shots = getShotsForPlayer(player);
    
  float sum = 0;
  float countInZone = 0;

  for (int i = 0; i < count; i++) {
    if (shots[i].zone == zone) {
      sum += shots[i].split;
      countInZone++;
    }
  }

  return countInZone == 0 ? 0 : sum/countInZone;
}

int getPlayerSplitStatus(int player, float split) {
  shot* shots = getShotsForPlayer(player);
  int count = getShotCountForPlayer(player);

  if (count == 0)
    return 0;
  else if (split < shots[0].split)
    return 1;
  else if (split > shots[count - 1].split)
    return -1;

  return 0;
}

static float lerp(float x0, float y0, float x1, float y1, float x) {
    float dx1 = x1 - x;
    float dx0 = x - x0;
    return (y0*dx1 + y1*dx0)/(x1 - x0);
}

int getZoneforPlayerSplit(int player, float split) {
  int count = getShotCountForPlayer(player);
  shot* shots = getShotsForPlayer(player);

  if (count == 0)
    return -1;
  else if (split < shots[0].split)
    return shots[0].zone;
  else if (split > shots[count - 1].split)
    return shots[count - 1].zone;

  int leftIndex = 0;
  int rightIndex = 0;
  for (int i = 0; i < count; i++) {
    if (split >= shots[i].split && split <= shots[i+1].split) {
        leftIndex = i;
        rightIndex = i + 1;
        break;
    }
  }

  float x0 = shots[leftIndex].split;
  float y0 = shots[leftIndex].zone;
  float x1 = shots[rightIndex].split;
  float y1 = shots[rightIndex].zone;

  float y = lerp(x0, y0, x1, y1, split);

  return (int)round(y);
}