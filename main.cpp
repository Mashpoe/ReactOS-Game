#include <iostream>

#include "Display.hpp"
#include "Texture.hpp"
#include "Color.hpp"
#include "Transparency.hpp"

int main()
{
    Game::Display d;
    d.setColor(Game::BG_BLACK);

    Game::Texture player;
    player.load("player.txt");
    player.setTransparency(Game::TRANSPARENT_BG);
    player.setColor(Game::FG_WHITE);

    Game::Texture owl;
    owl.load("owl.txt");
    owl.setColor(Game::FG_BLACK | Game::BG_YELLOW);

    Game::Texture trunk;
    trunk.load("trunk.txt");
    trunk.setColor(Game::FG_BLACK | Game::BG_RED);

    Game::Texture branches;
    branches.load("branches.txt");
    branches.setTransparency(Game::TRANSPARENT_BG);
    branches.setColor(Game::FG_RED);

    Game::Texture leaves;
    leaves.load("leaves.txt");
    leaves.setTransparency(Game::TRANSPARENT_BG);
    leaves.setColor(Game::FG_LIGHT_GREEN);

    Game::Texture moon;
    moon.load("moon.txt");
    moon.setColor(Game::FG_GRAY | Game::BG_WHITE);

    d.clear(' ');

    int treeX = 6;
    int treeY = d.getHeight() - trunk.getHeight();

    trunk.render(d, treeX, treeY);
    branches.render(d, treeX, treeY);
    leaves.render(d, treeX, treeY);
    owl.render(d, treeX + 15, treeY + 4);
    player.render(d, 25, 22);
    moon.render(d, 37, 13);

    d.render();

    return 0;
}
