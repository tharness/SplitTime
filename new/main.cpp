#include "stopwatch.hpp"

#include <iostream>

int main() {
    Stopwatch::Stopwatch stopwatch;
    char command;
    std::cout << "Commands:\n" << "\ts (start/stop)\n" << "\tm (mode)\n" << "\tu (up)\n" << "\td (down)\n" << std::endl;
    while (std::cin >> command) {
        switch (command) {
            case 's':
                stopwatch.handleEvent(Stopwatch::START_STOP);
                break;
            case 'm':
                stopwatch.handleEvent(Stopwatch::MODE);
                break;
            case 'u':
                stopwatch.handleEvent(Stopwatch::UP);
                break;
            case 'd':
                stopwatch.handleEvent(Stopwatch::DOWN);
                break;
            default:
                std::cout << "invalid event\n";
                break;
        }
    }

    return 0;
}
