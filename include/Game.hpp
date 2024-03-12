/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Game
*/

#ifndef ARCADE_GAME_HPP
#define ARCADE_GAME_HPP

#include "Exception.hpp"
#include "Graphical.hpp"

namespace arc {
    /**
     * @brief Interface for the game
     */
    class Game {
    public:
        /**
         * @brief Exception for the game
         */
        class GameException : public Exception {
        public:
            GameException(const std::string &name, const std::string &message) : Exception(name, message) {}
        };

        /**
         * @brief Initialize the game
         */
        virtual void init() = 0;
        /**
         * @brief Stop the game and free the memory
         */
        virtual void stop() = 0;

        /**
         * @brief Event for the game (example: keyboard input, mouse input, etc.)
         */
        virtual void event() = 0;
        /**
         * @brief Update the game
         */
        virtual void update() = 0;
        /**
         * @brief Draw the game (example: draw the map, draw the player, etc.)
         * @warning This function should not call the display function of the graphical library
         *
         * @param graphical Graphical library to draw the game
         */
        virtual void draw(Graphical &graphical) = 0;
    };
}

#endif //ARCADE_GAME_HPP
