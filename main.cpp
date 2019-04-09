#include <iostream>

#include "Display.hpp"
#include "Texture.hpp"
#include "Color.hpp"

int main()
{
    Game::Display d;
    d.setColor(Game::BG_AQUA);

    Game::Texture bg;
    bg.load("clouds.txt");
    bg.setColor(Game::FG_WHITE | Game::BG_WHITE);

    Game::Texture player;
    player.load("player.txt");
    player.setTransparency(Game::TRANSPARENT_BG);
    player.setColor(Game::FG_BLACK);

    int px = 0, py = 0, xvel = 1, yvel = 1;

    for (;;) {
        d.clear(' ');

        bg.render(d, 0, 0);

        player.render(d, px, py);
        d.writeString("- WEEEEE!", px + 4, py);

        px+=xvel;
        py+=yvel;

        if (xvel == 1) {
            if (px > d.getWidth()) {
                xvel = -1;
            }
        } else if (px <= 0) {
            xvel = 1;
        }

        if (yvel == 1) {
            if (py > d.getHeight()) {
                yvel = -1;
            }
        } else if (py <= 0) {
            yvel = 1;
        }

        d.render();

        Sleep(5);

    }




    return 0;
}
