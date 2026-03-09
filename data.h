#ifndef DATA_H
#define DATA_H

extern const char* PLAYERS[];

typedef struct shot {
  float split;
  int zone;
} shot;

void addShotForPlayer(int player, float split, int zone);
int getShotCountForPlayer(int player);
shot* getShotsForPlayer(int player);

#endif // DATA_H