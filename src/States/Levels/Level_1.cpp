#include <iostream>
#include "States/Levels/Level_1.hpp"
#include "Assets/Player.hpp"

using namespace States::Levels;

void Level_1::initializeLevel()
{
    this->addEntity<Assets::Player>();
}