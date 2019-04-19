#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "State.hpp"
#include "Texture.hpp"
#include <vector>

enum GameDirection {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

class GameState : public State {

    static GameState instance;

    static const int TILE_WIDTH = 8, TILE_HEIGHT = 4;

    std::vector<std::vector<int>> world;

    Game::Rect player = { 10, 10, 6, 5};

    Game::Texture playerImg;

    Game::Texture blocks;

    bool up = false, down = false, left = false, right = false;

    float xVel = 0.0f, yVel = 0.0f;
    float acc = 0.5f;
    float xMaxVel = 3, yMaxVel = 3;

public:

    void cleanup();

    void handleKeyDown(WORD keyCode);
    void handleKeyUp(WORD keyCode);

    void update();
    void render(Game::Display& display);

    static GameState* Instance() {
        return &instance;
    }

    // if move is true, the entity will be moved
    // outside of the block it's touching based on its direction
    bool handleCollision(Game::Rect* entity, bool move = false, GameDirection dir = DIR_UP);

protected:
    GameState() {}; // protected constructor for singleton

    void setup();
};

#endif // GAMESTATE_HPP_INCLUDED
