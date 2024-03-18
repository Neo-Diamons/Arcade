/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Game
*/

#ifndef ARCADE_IGAME_HPP
#define ARCADE_IGAME_HPP

#include "Exception.hpp"
#include "IGraphical.hpp"

namespace arc {
    /**
     * @interface IGame
     * @brief Interface for the game
     */
    class IGame {
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
         * @param key Key input
         */
        virtual void event(IKey *key) = 0;
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
        virtual void draw(IGraphical &graphical) = 0;
    };
}

#endif //ARCADE_IGAME_HPP