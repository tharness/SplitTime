#include "states.h"
#include "data.h"
#include "LCD.h"
#include "OLED.h"

LCD lcd;
Display& lcd_display = lcd;
OLED oled;
Display& oled_display = oled;

void initDraw(int fps) {
    lcd_display.begin(fps);
    oled_display.begin(fps);
}
void clear() {
    lcd_display.clear();
    oled_display.clear();
}
void drawState(Stopwatch::State s, const Stopwatch::Data& d) {
    lcd_display.drawState(s, d);
    oled_display.drawState(s, d);
}