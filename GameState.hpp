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

struct Entity {
    double x;
    double y;
    double w;
    double h;
};

class GameState : public State {

    static GameState instance;

    static const int TILE_WIDTH = 8, TILE_HEIGHT = 4;

    std::vector<std::vector<int>> world;

    //double playerX = 10, playerY = 10;
    Entity player = { 10, 10, 4, 4};
    std::vector<Game::Rect> frames = {
        {0, 0, 4, 5},
        {0, 5, 4, 5},
        {0, 10, 4, 5},
        {0, 15, 4, 5},
        {0, 20, 4, 5},
        {0, 25, 4, 5}
    };
    int currentFrame = 0;

    Game::Texture playerImg;

    Game::Texture blocks;

    bool up = false, down = false, left = false, right = false;

    float xVel = 0.0f, yVel = 0.0f;
    float acc = 0.05f;
    float xMaxVel = 1.0f, yMaxVel = 3.0f;
    float gravity = 0.05f;
    float jumpForce = 1.0f;

    bool touchingGround = false;

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
    bool handleCollision(Entity* e, bool move = false, GameDirection dir = DIR_UP);

protected:
    GameState() {}; // protected constructor for singleton

    void setup();
};

#endif // GAMESTATE_HPP_INCLUDED
