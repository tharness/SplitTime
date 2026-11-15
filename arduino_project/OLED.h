#ifndef OLED_H
#define OLED_H

#include "states.h"
#include "data.h"
#include "display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED : public Display {
public:
    void clear() override;
    void begin(int fps) override;
    void drawState(Stopwatch::State s, const Stopwatch::Data& d) override;
private:
    const int OLED_WIDTH = 128;
    const int OLED_HEIGHT = 64;
    Adafruit_SSD1306 oled{OLED_WIDTH, OLED_HEIGHT};
    long stateStartMs = 0;
    long currentMs = 0;

    void draw_IDLE(const Stopwatch::Data d) override;
    void draw_RUNNING(const Stopwatch::Data d) override;
    void draw_ZONE_PREDICT(const Stopwatch::Data d) override;
    void draw_SPLIT_PREDICT(const Stopwatch::Data d) override;
    void draw_SAVE_SELECT(const Stopwatch::Data d) override;

    void printText(const char* text, int size, int x, int y);
    void getTextCenter(const char* text, int size, int x, int y, int* outX, int* outY);
    void printTextRightJustified(const char* text, int size, int x, int y);
    void printTextBottomJustified(const char* text, int size, int x, int y);

    void drawPlayer(int pos);
    void drawStopWatchIcon();
    void drawZoneIcon();
    void drawNoSaveIcon(int save, int pos);
    void drawSplit(float split);
    void drawConfidence(float conf, bool right);
    void drawZone(int zone);
    bool cursorOn();
};

#endif // OLED_H