#ifndef DATA_H
#define DATA_H

static const char* PLAYERS[4] = {
  "Lead",
  "Second",
  "Third",
  "Skip"
};

static const unsigned char ROCK_DATA[8] = {
  0b00000,
  0b01110,
  0b01000,
  0b11111,
  0b10001,
  0b11111,
  0b00000,
  0b00000
};
static const unsigned char ROCK_DATA_90[8] = {
  0b00000,
  0b00100,
  0b00100,
  0b11111,
  0b10001,
  0b11111,
  0b00000,
  0b00000
};
static const unsigned char ROCK_DATA_180[8] = {
  0b00000,
  0b01110,
  0b00010,
  0b11111,
  0b10001,
  0b11111,
  0b00000,
  0b00000
};
static const unsigned char *ROCK_DATA_270 = ROCK_DATA_90;

static const unsigned char ROCK_CHAR = 0;
static const unsigned char ROCK_CHAR_90 = 1;
static const unsigned char ROCK_CHAR_180 = 2;
static const unsigned char ROCK_CHAR_270 = 3;

static const unsigned char ROCK_ROTATIONS[4] = { ROCK_CHAR, ROCK_CHAR_90, ROCK_CHAR_180, ROCK_CHAR_270 };

#endif // DATA_H