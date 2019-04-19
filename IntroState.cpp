#include "IntroState.hpp"
#include "GameState.hpp"

IntroState IntroState::instance;

void IntroState::setup() {

}

void IntroState::cleanup() {

}

void IntroState::handleKeyDown(WORD keyCode) {

}

void IntroState::handleKeyUp(WORD keyCode) {

}

void IntroState::update() {

    frameCount++;

    if (frameCount > maxFrames) {
        game->changeState(GameState::Instance());
    }

}

void IntroState::render(Game::Display& display) {
    display.clear(' ');
    display.writeString(message, 10, 10);
}
