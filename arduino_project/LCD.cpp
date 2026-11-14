#include "LCD.h"

void LCD::begin(int fps) {
    frames_per_second = fps;
    lcd.begin(LCD_COLS, LCD_ROWS);
}

void LCD::clear() {
  lcd.clear();
  frame_counter = 0;
}

void LCD::draw_IDLE(const Stopwatch::Data d) {
    char* positions[] = {"Lead", "Second", "Third", "Skip"};
    lcd.setCursor(0, 0);
    lcd.write(positions[d.position]);
    lcd.setCursor(8, 0);
    lcd.write((String(d.predictor_by_position[d.position].confidence * 100, 0) + "%").c_str());
    lcd.setCursor(0, 1);
    lcd.write(String(d.split).c_str());
    if (!d.saveShots) { lcd.setCursor(15, 0); lcd.write("!"); }
}

void LCD::draw_RUNNING(const Stopwatch::Data d) {
    char* positions[] = {"Lead", "Second", "Third", "Skip"};
    lcd.setCursor(0, 0);
    lcd.write(positions[d.position]);
    lcd.setCursor(8, 0);
    lcd.write((String(d.predictor_by_position[d.position].confidence * 100, 0) + "%").c_str());
    lcd.setCursor(0, 1);
    lcd.write(String(d.split).c_str());
    if (!d.saveShots) { lcd.setCursor(15, 0); lcd.write("!"); }
}

void LCD::draw_ZONE_PREDICT(const Stopwatch::Data d) {
    char* positions[] = {"Lead", "Second", "Third", "Skip"};
    lcd.setCursor(0, 0);
    lcd.write(positions[d.position]);
    lcd.setCursor(8, 0);
    lcd.write((String(d.predictor_by_position[d.position].confidence * 100, 0) + "%").c_str());
    lcd.setCursor(0, 1);
    lcd.write(String(d.split).c_str());
    lcd.setCursor(8, 1);
    if (d.zone == -1 && frame_counter < frames_per_second) lcd.write("_");
    else if (d.zone == -1 && frame_counter >= frames_per_second) lcd.write(" ");
    else if (d.zone == 0) lcd.write("HOG");
    else if (d.zone == 11) lcd.write("THROUGH");
    else lcd.write(String(d.zone).c_str());
    if (!d.saveShots) { lcd.setCursor(15, 0); lcd.write("!"); }
}

void LCD::draw_SPLIT_PREDICT(const Stopwatch::Data d) {
    char* positions[] = {"Lead", "Second", "Third", "Skip"};
    lcd.setCursor(0, 0);
    lcd.write(positions[d.position]);
    lcd.setCursor(8, 0);
    lcd.write((String(d.predictor_by_position[d.position].confidence * 100, 0) + "%").c_str());
    lcd.setCursor(0, 1);
    lcd.write(String(d.split).c_str());
    lcd.setCursor(8, 1);
    if (frame_counter < frames_per_second) lcd.write(String(d.zone).c_str());
    else lcd.write(" ");
    if (!d.saveShots) { lcd.setCursor(15, 0); lcd.write("!"); }
}

void LCD::draw_SAVE_SELECT(const Stopwatch::Data d) {
    lcd.setCursor(0, 0);
    lcd.write("Overwrite data?");
    lcd.setCursor(0, 1);
    if (d.saveShots) lcd.write("Yes");
    else lcd.write("No");
    lcd.setCursor(4, 1);
    if (frame_counter < frames_per_second) lcd.write("<");
    else lcd.write(" ");
}

void LCD::drawState(Stopwatch::State s, const Stopwatch::Data& d) {
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