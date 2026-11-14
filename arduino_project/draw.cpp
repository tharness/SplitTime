#include "states.h"
#include "data.h"
#include "LCD.h"

LCD lcd;
Display& lcd_display = lcd;

void initDraw(int fps) {
    lcd_display.begin(fps);
}
void clear() {
    lcd_display.clear();
}
void drawState(Stopwatch::State s, const Stopwatch::Data& d) {
    lcd_display.drawState(s, d);
}