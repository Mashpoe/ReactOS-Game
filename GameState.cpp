#include "GameState.hpp"
#include "Color.hpp"

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
        break;
    case VK_RIGHT:
        right = true;
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
    if (up) {
        player.y--;
        handleCollision(&player, true, DIR_UP);
    }
    if (down) {
        player.y++;
        handleCollision(&player, true, DIR_DOWN);
    }
    if (left) {
        player.x--;
        handleCollision(&player, true, DIR_LEFT);
    }
    if (right) {
        player.x++;
        handleCollision(&player, true, DIR_RIGHT);
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

    playerImg.render(display, player.x, player.y-1);
}

bool GameState::handleCollision(Game::Rect* entity, bool move, GameDirection dir) {

    for (int x = entity->x/TILE_WIDTH; x < (entity->x+entity->w-1)/TILE_WIDTH + 1; x++) {
        for (int y = entity->y/TILE_HEIGHT; y < (entity->y+entity->h-1)/TILE_HEIGHT + 1; y++) {

            if (move) {
                // do bounds checking
                if (x >= 0 && x < world.size() && y >= 0 && y < world[x].size()) {
                    if (world[x][y] > 0) {
                        switch (dir) {
                        case DIR_UP:
                            entity->y = (y+1) * TILE_HEIGHT;
                            break;
                        case DIR_DOWN:
                            entity->y = y*TILE_HEIGHT - entity->h;
                            break;
                        case DIR_LEFT:
                            entity->x = (x+1) * TILE_WIDTH;
                            break;
                        case DIR_RIGHT:
                            entity->x = x*TILE_WIDTH - entity->w;
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
