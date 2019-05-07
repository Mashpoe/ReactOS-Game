#include "GameState.hpp"
#include "Color.hpp"
#include <algorithm>
#include <math.h>
#include <sstream>

GameState GameState::instance;

void GameState::setup() {

    Game::Display& d = game->getDisplay();

    camX = d.getWidth() / 2;
    camY = d.getHeight() / 2;


    world.create();

    /*world = {
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,1,1,1},
        {1,0,0,1,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,1}
    };*/

    // load the player texture
    playerImg.load("player.txt");
    playerImg.setTransparency(Game::TRANSPARENT_BG);
    playerImg.setColor(Game::FG_LIGHT_YELLOW);

    blocks.load("blocks.txt");
    blocks.setBackground('\0');
    blocks.setColor(Game::FG_GREEN | Game::BG_RED);

}

void GameState::cleanup() {

}

void GameState::handleKeyDown(WORD keyCode) {

    switch (keyCode) {
    case 0x57: // W
        up = true;
        break;
    case 0x53: // S
        down = true;
        break;
    case 0x41: // A
        left = true;
        currentFrame = 0;
        break;
    case 0x44: // D
        right = true;
        currentFrame = 3;
        break;
    case VK_SPACE:
        jump = true;
        break;
    case 0x51:
        game->quit();
        break;
    }

}

void GameState::handleKeyUp(WORD keyCode) {
    switch (keyCode) {
    case 0x57: // W
        up = false;
        break;
    case 0x53: // S
        down = false;
        break;
    case 0x41: // A
        left = false;
        break;
    case 0x44: // D
        right = false;
    case VK_SPACE:
        jump = false;
        break;
    }
}

void GameState::handleMouseEvent(MOUSE_EVENT_RECORD* event) {
    mouseX = event->dwMousePosition.X;
    mouseY = event->dwMousePosition.Y;

    mouseLeft = event->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED;
    mouseRight = event->dwButtonState & RIGHTMOST_BUTTON_PRESSED;
}

void GameState::update() {

    if (xVel != 0 && !left && !right) {
        if (xVel > 0) {
            xVel = std::max<float>(xVel - acc, 0);
        } else {
            xVel = std::min<float>(xVel + acc, 0);
        }
    } else {

        if (left && xVel > -xMaxVel) {
            xVel = std::max<float>(xVel - acc, -xMaxVel);
        }

        if (right && xVel < xMaxVel) {
            xVel = std::min<float>(xVel + acc, xMaxVel);
        }

    }

    player.x += xVel;

    if (xVel != 0 &&
        handleCollision(
            &player,
            true,
            (xVel > 0) ? DIR_RIGHT:DIR_LEFT
        ))
    {
        xVel = 0;
    }

    if (jump && touchingGround) {
        yVel -= jumpForce;
    } else if (yVel < yMaxVel) {
        yVel = std::min<float>(yVel + gravity, yMaxVel);
    }

    player.y += yVel;

    if (yVel > 0) {
        touchingGround = handleCollision(&player, true, DIR_DOWN);
        if (touchingGround) {
            yVel = 0;
        }
    } else if (yVel < 0) {
        if (handleCollision(&player, true, DIR_UP)) {
            yVel = 0;
        }
        touchingGround = false;
    }

    world.updateChunks(player);

    // mining blocks
    if (mouseLeft || mouseRight) {
        int mouseBlockX = (mouseX-camX+(int)player.x)/TILE_WIDTH;
        int mouseBlockY = (mouseY-camY+(int)player.y)/TILE_HEIGHT;

        if (mouseBlockX < world.width() &&
            mouseBlockY < world.height() &&
            mouseBlockX >= 0 &&
            mouseBlockY >= 0) {
            world.set(mouseBlockX,mouseBlockY, mouseRight?1:0);
        }
    }

}

void GameState::render(Game::Display& display) {
    display.setColor(Game::BG_AQUA | Game::FG_LIGHT_YELLOW);
    display.clear(' ');

    for (int x = 0; x < world.width(); x++) {
        for (int y = 0; y < world.height(); y++) {
            if (world.get(x,y) > 0) {
                blocks.render(display, x*TILE_WIDTH-(int)player.x+camX, y*TILE_HEIGHT-(int)player.y+camY);
            }
        }
    }

    int mouseBlockX = mouseX - (mouseX+camX+(int)player.x)%TILE_WIDTH;
    int mouseBlockY = mouseY - (mouseY+camY+(int)player.y)%TILE_HEIGHT;
    display.setTransparency(Game::TRANSPARENT_BG);


    display.setColor(Game::FG_WHITE);
    display.setChar(0xC9, mouseBlockX, mouseBlockY);
    display.drawLine(0xCD, mouseBlockX + 1, mouseBlockY, mouseBlockX + TILE_WIDTH - 2, mouseBlockY);
    display.setChar(0xBB, mouseBlockX + TILE_WIDTH - 1, mouseBlockY);
    display.drawLine(0xBA, mouseBlockX, mouseBlockY + 1, mouseBlockX, mouseBlockY + TILE_HEIGHT - 2);
    display.setChar(0xC8, mouseBlockX, mouseBlockY + TILE_HEIGHT - 1);
    display.drawLine(0xCD, mouseBlockX + 1, mouseBlockY + TILE_HEIGHT - 1, mouseBlockX + TILE_WIDTH - 2, mouseBlockY + TILE_HEIGHT - 1);
    display.setChar(0xBC, mouseBlockX + TILE_WIDTH - 1, mouseBlockY + TILE_HEIGHT - 1);
    display.drawLine(0xBA, mouseBlockX + TILE_WIDTH - 1, mouseBlockY + TILE_HEIGHT - 2, mouseBlockX + TILE_WIDTH - 1, mouseBlockY + 1);

    playerImg.render(display, camX, camY-1, &frames[currentFrame]);

    std::ostringstream strs;
    strs << player.x;
    strs << ", ";
    strs << player.y;
    display.writeString(strs.str().c_str(), 1, 1);

    std::ostringstream strs2;
    strs2 << world.getOffsetX();
    strs2 << ", ";
    strs2 << world.getOffsetY();
    display.writeString(strs2.str().c_str(), 1, 2);

}

bool GameState::handleCollision(Entity* e, bool move, GameDirection dir) {

    for (int x = (int)floor(e->x)/TILE_WIDTH; x < (int)ceil(e->x+e->w-1)/TILE_WIDTH + 1; x++) {
        for (int y = e->y/TILE_HEIGHT; y < (int)ceil(e->y+e->h-1)/TILE_HEIGHT + 1; y++) {

            if (move) {
                // do bounds checking
                if (x >= 0 && x < world.width() && y >= 0 && y < world.height()) {

                    if (world.get(x, y) > 0) {
                        switch (dir) {
                        case DIR_UP:
                            e->y = (y+1) * TILE_HEIGHT;
                            break;
                        case DIR_DOWN:
                            e->y = y*TILE_HEIGHT - e->h;
                            break;
                        case DIR_LEFT:
                            e->x = (x+1) * TILE_WIDTH;
                            break;
                        case DIR_RIGHT:
                            e->x = x*TILE_WIDTH - e->w;
                            break;
                        }
                        return true;
                    }
                }
            }
        }
    }

    return false;

}
