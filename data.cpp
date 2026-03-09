#include "data.h"
#include <stdlib.h>

static const char* PLAYERS[4] = {
  "Lead",
  "Second",
  "Third",
  "Skip"
};

int compareShots(const void* a, const void* b)
{
  shot arg1 = *(const shot*)a;
  shot arg2 = *(const shot*)b;
 
  if (arg1.split < arg2.split) return -1;
  if (arg1.split > arg2.split) return 1;
  return 0;
}

static shot playerShots[4][30];
static int playerShotCount[4] = { 0 };

void addShotForPlayer(int player, float split, int zone) {
  shot s = { split, zone };

  int shotIndex = playerShotCount[player];
  playerShots[player][shotIndex] = s;

  playerShotCount[player]++;
  int count = playerShotCount[player];
  
  qsort(playerShots[player], count, sizeof(shot), compareShots);
}

int getShotCountForPlayer(int player) {
  return playerShotCount[player];
}

shot* getShotsForPlayer(int player) {
  return playerShots[player];
}