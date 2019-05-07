#include "Game.hpp"
#include "State.hpp"

StateManager::StateManager() {

}

void StateManager::update() {

    INPUT_RECORD event;

    while (display.pollEvent(&event)) {

        if (!states.empty()) {
            switch (event.EventType) {
            case KEY_EVENT:
                if (event.Event.KeyEvent.bKeyDown) {
                    states.back()->handleKeyDown(event.Event.KeyEvent.wVirtualKeyCode);
                } else {
                    states.back()->handleKeyUp(event.Event.KeyEvent.wVirtualKeyCode);
                }
                break;
            case MOUSE_EVENT:
                states.back()->handleMouseEvent(&event.Event.MouseEvent);
                break;
            }
        }

    }

    if (!states.empty()) {
        states.back()->update();
    }

}

void StateManager::render() {
    if (!states.empty()) {
        states.back()->render(display);
    }
    display.render();
}

void StateManager::pushState(State* state) {

    if (!states.empty()) {
        states.back()->pause();
    }

    states.push_back(state);
    states.back()->init(this);
}

void StateManager::popState() {
    if (!states.empty()) {
        states.back()->cleanup();
        states.pop_back();
    }

    if (!states.empty()) {
        states.back()->resume();
    }
}

void StateManager::changeState(State* state) {
    if (!states.empty()) {
        states.back()->cleanup();
        states.pop_back();
    }

    pushState(state);
}
