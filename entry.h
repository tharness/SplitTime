#ifndef ENTRY_H
#define ENTRY_H

// Entry handlers (called when entering a state)
void defaultEntry();
void idleEntry();
void stopwatchStoppedEntry();
void stopwatchCountingEntry();
void splitPredictEntry();

#endif // ENTRY_H