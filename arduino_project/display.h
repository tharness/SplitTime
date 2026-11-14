#ifndef DISPLAY_H
#define DISPLAY_H

#include "states.h"
#include "data.h"

class Display {
public:
    virtual void begin(int fps);
    virtual void clear() = 0;
    void drawState(Stopwatch::State s, const Stopwatch::Data& d);
protected:
    int frames_per_second = 60;
    int frame_counter = 0;
private:
    virtual void draw_IDLE(const Stopwatch::Data d) = 0;
    virtual void draw_RUNNING(const Stopwatch::Data d) = 0;
    virtual void draw_ZONE_PREDICT(const Stopwatch::Data d) = 0;
    virtual void draw_SPLIT_PREDICT(const Stopwatch::Data d) = 0;
    virtual void draw_SAVE_SELECT(const Stopwatch::Data d) = 0;
};

#endif // DISPLAY_H