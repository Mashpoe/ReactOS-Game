#ifndef INTROSTATE_HPP_INCLUDED
#define INTROSTATE_HPP_INCLUDED

#include "State.hpp"

class IntroState : public State {

    static IntroState instance;

    int frameCount = 0;
    int maxFrames = 100;

    const char* message = "ReactOS Game!";

public:

    void cleanup();

    void handleKeyDown(WORD keyCode);
    void handleKeyUp(WORD keyCode);

    void update();
    void render(Game::Display& display);

    static IntroState* Instance() {
        return &instance;
    }

protected:
    IntroState() {}; // protected constructor for singleton

    void setup();
};

#endif // INTROSTATE_HPP_INCLUDED
