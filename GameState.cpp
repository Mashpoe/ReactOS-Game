#include "GameState.hpp"
#include "Color.hpp"
#include <algorithm>
#include <math.h>

GameState GameState::instance;

void GameState::setup() {

    // generate the world
    /*for (int x = 0; x < 20; x++) {
        world.push_back(std::vector<int>());
        for (int y = 0; y < 20; y++) {
            int block = y > 4? 1:0;
            world[x].push_back(block);
        }
    }*/

    world = {
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,0,0,1,1,1},
        {1,0,0,1,0,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,1},
        {1,1,1,1,1,1}
    };

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
    case VK_UP:
        up = true;
        break;
    case VK_DOWN:
        down = true;
        break;
    case VK_LEFT:
        left = true;
        currentFrame = 0;
        break;
    case VK_RIGHT:
        right = true;
        currentFrame = 3;
        break;
    case 0x51:
        game->quit();
        break;
    }

}

void GameState::handleKeyUp(WORD keyCode) {
    switch (keyCode) {
    case VK_UP:
        up = false;
        break;
    case VK_DOWN:
        down = false;
        break;
    case VK_LEFT:
        left = false;
        break;
    case VK_RIGHT:
        right = false;
        break;
    }
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

    if (up && touchingGround) {
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

}

void GameState::render(Game::Display& display) {
    display.setColor(Game::BG_AQUA | Game::FG_LIGHT_YELLOW);
    display.clear(' ');



    for (int x = 0; x < world.size(); x++) {
        for (int y = 0; y < world[x].size(); y++) {
            if (world[x][y] > 0) {
                blocks.render(display, x*TILE_WIDTH, y*TILE_HEIGHT);
            }
        }
    }

    playerImg.render(display, player.x, player.y-1, &frames[currentFrame]);
}

bool GameState::handleCollision(Entity* e, bool move, GameDirection dir) {

    for (int x = e->x/TILE_WIDTH; x < (int)((e->x+e->w-1)/TILE_WIDTH) + 1; x++) {
        for (int y = e->y/TILE_HEIGHT; y < (int)((e->y+e->h-1)/TILE_HEIGHT) + 1; y++) {

            if (move) {
                // do bounds checking
                if (x >= 0 && x < world.size() && y >= 0 && y < world[x].size()) {
                    if (world[x][y] > 0) {
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
