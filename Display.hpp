#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <windows.h>
#include "Transparency.hpp"

namespace Game {

    class Display {
    friend class Texture;
    private:
        int width, height;

        // a "2d" array of character pixels
        CHAR_INFO* display;

        // the output console that we will be rendering to
        HANDLE window;
        HANDLE input;

        // the current render color
        WORD color = 0x0F;

        Transparency transparency = TRANSPARENT_NO;

        // write area for the render function
        SMALL_RECT writeArea;

        WORD getDrawColor(unsigned int x, unsigned int y);

        INPUT_RECORD inputBuff[128];
        DWORD inputCount = 0;
        int currentInput = 0;

    public:

        Display(HANDLE window = GetStdHandle(STD_OUTPUT_HANDLE),
                HANDLE input = GetStdHandle(STD_INPUT_HANDLE));

        void render();

        // fill the entire screen with one character
        void clear(char c);

        void setColor(WORD color) { this->color = color; }
        WORD getColor() { return color; }

        void setTransparency(Transparency transparency) { this->transparency = transparency; }
        Transparency getTransparency() { return transparency; }

        // use unsigned so no negative values are allowed
        void setChar(char c, unsigned int x, unsigned int y);

        void writeString(const char* s, int x, int y);

        void drawLine(char c, int x1, int y1, int y2, int x2);

        int getWidth() { return width; }
        void setWidth(int width) { this->width = width; }

        int getHeight() { return height; }
        void setHeight() { this->height = height; }

        bool pollEvent(INPUT_RECORD* event);

    };

}

#endif // DISPLAY_HPP_INCLUDED
