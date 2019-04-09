#include "Texture.hpp"
#include <fstream>
#include <math.h>

namespace Game {

    bool Texture::load(const char* path) {

        std::ifstream f(path);

        if (!f.is_open()) {
            return false;
        }

        bounds = {0, 0, 0, 0};

        std::string currentLine;
        while (std::getline(f, currentLine)) {
            data.push_back(currentLine);
            if (currentLine.length() > bounds.w) {
                bounds.w = currentLine.length();
            }
            bounds.h++;
        }

        f.close();

        return true;

    }

    void Texture::render(Display& d, int x, int y, Rect* src) {

        if (src == NULL) {
            src = &bounds; // use default bounds
        }

        int startY = std::max(0, y);
        int endY = std::min<int>(y + src->h, d.height);
        int startX = std::max(0, x);
        for (int r = startY; r < endY; r++) {

            int rowPos = r-y+src->y;

            int rowWidth = std::min<int>(src->w, data[rowPos].size());
            int endX = std::min<int>(x + rowWidth, d.width);

            for (int c = startX; c < endX; c++) {

                char currentChar = data[rowPos][c-x+src->x];

                if (currentChar != background) {

                    CHAR_INFO* ci = &d.display[r*d.width + c];

                    WORD currentColor = color;
                    if (transparency != TRANSPARENT_NO) {

                        if (transparency == TRANSPARENT_BG) {
                            currentColor &= 0x0F; // clear bg bits
                            currentColor |= ci->Attributes & 0xF0;
                        } else {
                            currentColor &= 0xF0; // clear fg bits
                            currentColor |= (ci->Attributes >> 4) & 0x0F;
                        }

                    }


                    ci->Char.AsciiChar = currentChar;
                    ci->Attributes = currentColor;
                }

            }
        }

    }

}
