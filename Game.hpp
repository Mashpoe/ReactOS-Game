#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Display.hpp"
#include <vector>

class State;

class StateManager {

    std::vector<State*> states;

    Game::Display display;

    bool isRunning = true;

public:

    StateManager();

    void update();
    void render();

    void pushState(State* state);
    void popState();
    void changeState(State* state);

    void quit() { isRunning = false; }
    bool running() { return isRunning; }

    Game::Display& getDisplay() { return display; }

};

#endif // GAME_HPP_INCLUDED
