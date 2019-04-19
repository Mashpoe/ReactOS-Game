#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <vector>
#include <string>
#include "Display.hpp"
#include "Rect.hpp"
#include "Transparency.hpp"

namespace Game {

    class Texture {

        // texture data
        std::vector<std::string> data;

        WORD color = 0x0F;

        Transparency transparency = TRANSPARENT_NO;

        char background = ' '; // ignore this character

        // default src bounds for rendering
        // contains width and height
        Rect bounds = {0, 0, 0, 0};

    public:

        bool load(const char* path);

        void render(Display& display, int x, int y, Rect* src = NULL);

        int getWidth() { return bounds.w; }
        int getHeight() { return bounds.h; }

        void setColor(WORD color) { this->color = color; }
        WORD getColor() { return color; }

        void setBackground(char background) { this->background = background; }
        char getBackground() { return background; }

        void setTransparency(Transparency transparency) { this->transparency = transparency; }
        Transparency getTransparency() { return transparency; }

    };

}

#endif // TEXTURE_HPP_INCLUDED
