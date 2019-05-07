#include "Display.hpp"
#include <memory.h>
#include "Color.hpp"

namespace Game {

    Display::Display(HANDLE window, HANDLE input)
    : window(window), input(input)
    {

        SetConsoleMode(input, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

        // get the console size in characters
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(window, &csbi)) {

            width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

            writeArea = {0, 0, width, height};

            // create the display
            display = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * width * height);


        } else {
            // TODO:: error
        }
    }

    void Display::render() {

        WriteConsoleOutput(window, display, {width, height}, {0, 0}, &writeArea);

    }

    void Display::clear(char c) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                display[y*width + x].Char.AsciiChar = c;
                display[y*width + x].Attributes = color;
            }
        }
    }

    void Display::setChar(char c, unsigned int x, unsigned int y) {
        if (x < width && y < height) {
            display[y*width + x].Char.AsciiChar = c;
            display[y*width + x].Attributes = getDrawColor(x, y);
        }
    }

    void Display::writeString(const char* s, int x, int y) {
        if (x >= width || y >= height || y < 0) {
            return;
        }
        int pos = 0;
        // pass over any characters that are outside of the window
        while (x + pos < 0) {
            if (s[pos] != '\0') {
                pos++;
            } else {
                return;
            }
        }
        while (s[pos] != '\0') {
            setChar(s[pos], x + pos, y);
            pos++;
        }
    }

    void Display::drawLine(char c, int x1, int y1, int x2, int y2) {
        int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
        int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1;
        int err = (dx>dy ? dx : -dy)/2, e2;

        for(;;){
            setChar(c, x1, y1);
            if (x1 == x2 && y1 == y2) {
                break;
            }
            e2 = err;
            if (e2 >-dx) { err -= dy; x1 += sx; }
            if (e2 < dy) { err += dx; y1 += sy; }
        }
    }

    WORD Display::getDrawColor(unsigned int x, unsigned int y) {

        CHAR_INFO* ci = &display[y*width + x];

        WORD drawColor = color;
        if (transparency != TRANSPARENT_NO) {

            if (transparency == TRANSPARENT_BG) {
                drawColor &= 0x0F; // clear bg bits
                drawColor |= ci->Attributes & 0xF0;
            } else {
                drawColor &= 0xF0; // clear fg bits
                drawColor |= (ci->Attributes >> 4) & 0x0F;
            }
        }

        return drawColor;

    }

    bool Display::pollEvent(INPUT_RECORD* event) {

        if (currentInput < inputCount) {
            *event = inputBuff[currentInput++];
            return true;
        }


        unsigned long eventCount;
        GetNumberOfConsoleInputEvents(input, &eventCount);

        if (eventCount == 0) {
            return false;
        }

        currentInput = 0;

        // read the next 128 events
        if (!ReadConsoleInput(
            input,          // input buffer handle
            inputBuff,      // buffer to read into
            128,            // size of read buffer
            &inputCount))   // number of records read
        {
            inputCount = 0;
            return false;
        }

        *event = inputBuff[currentInput++];

        return true;
    }

}
