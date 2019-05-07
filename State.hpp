#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include "Game.hpp"
#include "Display.hpp"
#include <Windows.h>

class State {
protected:
    StateManager* game;
    virtual void setup() {}; // user can override this to set up the state
public:

    void init(StateManager* game) {
        this->game = game;
        setup();
    }
    virtual void cleanup() {}

    virtual void handleKeyDown(WORD keyCode) = 0; // virtual key code
    virtual void handleKeyUp(WORD keyCode) = 0; // virtual key code
    virtual void handleMouseEvent(MOUSE_EVENT_RECORD* event) {};

    virtual void update() = 0;
    virtual void render(Game::Display& display) = 0;

    virtual void pause() {};
    virtual void resume() {};

};

#endif // STATE_HPP_INCLUDED
