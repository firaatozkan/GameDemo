/**
 * @file Level_1.cpp
 * @brief Implements the Level_1 class, a specific level derived from AbstractLevel.
 */

#include <iostream>
#include "States/Levels/Level_1.hpp"
#include "Assets/Player.hpp"

using namespace States::Levels;

/**
 * @brief Initializes the specific characteristics of Level_1.
 *
 * The initializeLevel method sets up the specific characteristics of Level_1,
 * such as adding entities like the player character to the level.
 */
void Level_1::initializeLevel()
{
    // Add the player entity to the level.
    this->addEntity<Assets::Player>();
}
