#ifndef DRAW_H
#define DRAW_H

void initDraw();
void flushDraw();

// Handler Functions

int defaultDraw();
int drawPlayer();
int drawIdle();
int drawStopped();
int drawSplitPredict();
int drawStopwatchCounting();

#endif // DRAW_H