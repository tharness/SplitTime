#include "states.h"
#include "data.h"
#include "display.h"
#include <LiquidCrystal.h>

class LCD : public Display {
public:
    void clear() override;
    void begin(int fps) override;
private:
    const int LCD_RS = 8;
    const int LCD_E = 9;
    const int LCD_D4 = 4;
    const int LCD_D5 = 5;
    const int LCD_D6 = 6;
    const int LCD_D7 = 7;
    const int LCD_COLS = 16;
    const int LCD_ROWS = 2;
    LiquidCrystal lcd{LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7};
    int frames_per_second = 60;
    int frame_counter = 0;

    void draw_IDLE(const Stopwatch::Data d) override;
    void draw_RUNNING(const Stopwatch::Data d) override;
    void draw_ZONE_PREDICT(const Stopwatch::Data d) override;
    void draw_SPLIT_PREDICT(const Stopwatch::Data d) override;
    void draw_SAVE_SELECT(const Stopwatch::Data d) override;
};