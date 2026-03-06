#ifndef DRAW_H
#define DRAW_H

void initDraw();
void flushDraw();

// Handler Functions

int defaultDraw();
int drawPlayer();
int drawRock();
int drawIdle();
int drawStopped();
int drawStopwatchCounting();

#endif // DRAW_H