/**
 * @file Level_1.hpp
 * @brief Defines the Level_1 class for the first game level.
 */

#pragma once

#include "States/Levels/AbstractLevel.hpp"

namespace States::Levels
{
    /**
     * @class Level_1
     * @brief Represents the first game level.
     *
     * The Level_1 class extends the AbstractLevel class to define the first game level.
     * It provides specific initialization for this level, including setting background colors.
     */
    class Level_1 : public AbstractLevel<Level_1>
    {
    private:
        friend class AbstractLevel<Level_1>;

        static constexpr int color_red = 108; /**< Red component of the background color. */
        static constexpr int color_green = 145; /**< Green component of the background color. */
        static constexpr int color_blue = 144; /**< Blue component of the background color. */
        static constexpr int color_alpha = 0; /**< Alpha component of the background color. */

        /**
         * @brief Initializes the first game level.
         *
         * This function sets up the initial state of the first game level, including
         * any necessary configurations and entity placement.
         */
        void initializeLevel();

    public:
        /**
         * @brief Default constructor for the first game level.
         */
        Level_1() = default;

        /**
         * @brief Destructor for cleaning up resources.
         */
        ~Level_1() = default;
    };
}
