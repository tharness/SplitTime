#include "display.h"

void Display::drawState(Stopwatch::State s, const Stopwatch::Data& d) {
    if (++frame_counter == 2*frames_per_second) frame_counter = 0;
    switch (s) {
        case Stopwatch::IDLE:
            draw_IDLE(d);
            break;
        case Stopwatch::RUNNING:
            draw_RUNNING(d);
            break; 
        case Stopwatch::ZONE_PREDICT:
            draw_ZONE_PREDICT(d);
            break;
        case Stopwatch::SPLIT_PREDICT:
            draw_SPLIT_PREDICT(d);
            break;
        case Stopwatch::SAVE_SELECT:
            draw_SAVE_SELECT(d);
            break;
    }
}