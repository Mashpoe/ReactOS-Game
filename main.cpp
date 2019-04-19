#include <iostream>

#include "Display.hpp"
#include "Texture.hpp"
#include "Color.hpp"
#include "Transparency.hpp"

int main()
{
    Game::Display d;

    Game::Texture player;
    player.load("player.txt");
    player.setTransparency(Game::TRANSPARENT_BG);
    player.setColor(Game::FG_PURPLE);

    Game::Texture owl;
    owl.load("owl.txt");
    owl.setColor(Game::FG_BLACK | Game::BG_YELLOW);

    Game::Texture trunk;
    trunk.load("trunk.txt");
    trunk.setColor(Game::FG_BLACK | Game::BG_RED);

    Game::Texture branches;
    branches.load("branches.txt");
    branches.setTransparency(Game::TRANSPARENT_BG);
    branches.setColor(Game::FG_RED);

    Game::Texture leaves;
    leaves.load("leaves.txt");
    leaves.setTransparency(Game::TRANSPARENT_BG);
    leaves.setColor(Game::FG_LIGHT_GREEN);

    Game::Texture moon;
    moon.load("moon.txt");
    moon.setColor(Game::FG_GRAY | Game::BG_WHITE);

    Game::Texture stars;
    stars.load("stars.txt");
    stars.setColor(Game::BG_BLACK | Game::FG_WHITE);

    Game::Texture log;
    log.load("log.txt");
    log.setColor(Game::FG_BLACK | Game::BG_RED);

    Game::Texture mushroom;
    mushroom.load("mushroom.txt");
    mushroom.setColor(Game::FG_WHITE | Game::BG_LIGHT_RED);

    int treeX = 20;
    int treeY = d.getHeight() - trunk.getHeight();

    int playerX = 42, playerY = 19;

    bool running = true;

    while (running) {


        INPUT_RECORD event;

        while (d.pollEvent(&event)) {

            switch(event.EventType) {
                case KEY_EVENT: // keyboard input
                    //KeyEventProc(event.Event.KeyEvent);
                    d.setChar(event.Event.KeyEvent.uChar.AsciiChar, 10, 10);
                    switch (event.Event.KeyEvent.wVirtualKeyCode) {
                    case VK_RIGHT:
                        playerX++;
                        break;
                    case VK_LEFT:
                        playerX--;
                        break;
                    case 0x51:
                        running = false;
                        break;
                    }
                    //running = false;
                    break;

                case MOUSE_EVENT: // mouse input
                    //MouseEventProc(event.Event.MouseEvent);
                    break;

                case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
                    //ResizeEventProc(event.Event.WindowBufferSizeEvent );
                    //running = false;
                    break;

                case FOCUS_EVENT:  // disregard focus events

                case MENU_EVENT:   // disregard menu events
                    break;

                default:
                    //running = false;
                    break;
            }

        }

        //d.setChar('a', 10, 10);
        d.setColor(Game::BG_BLACK);
        d.clear(' ');
        stars.render(d, 0, 0);
        moon.render(d, 65, 16);
    d.setColor(Game::FG_LIGHT_GREEN | Game::BG_GREEN);
    d.drawLine('^', 0, d.getHeight()-1, d.getWidth(), d.getHeight()-1);
        trunk.render(d, treeX, treeY);
        branches.render(d, treeX, treeY);
        leaves.render(d, treeX, treeY);
        owl.render(d, treeX + 15, treeY + 4);
        d.setColor(Game::BG_WHITE|Game::FG_BLACK);
        d.writeString(" WHOOO GOES THERE!?", treeX + 21, treeY + 2);
        d.setColor(Game::BG_BLACK|Game::FG_WHITE);
        d.setChar('/', treeX + 20, treeY + 3);
        player.render(d, playerX, playerY);
        log.render(d, 50, 23);
        mushroom.render(d, 55, 21);

        d.setColor(Game::FG_WHITE);

        d.render();

        Sleep(10);


    }

    return 0;
}
