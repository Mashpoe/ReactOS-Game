#include <iostream>

#include "Display.hpp"
#include "Texture.hpp"
#include "Color.hpp"
#include "Transparency.hpp"

#include "Game.hpp"
#include "IntroState.hpp"

int main()
{

    StateManager game;
    game.pushState(IntroState::Instance());

    while(game.running()) {
        game.update();
        game.render();
        Sleep(10);
    }

    return 0;
}
