/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Game
*/

#ifndef ARCADE_IGAME_HPP
#define ARCADE_IGAME_HPP

#include <list>
#include <cstdint>

#include "DrawObject/DrawObject.hpp"
#include "Exception.hpp"
#include "IKey.hpp"

namespace arc {
    /**
     * @interface IGame
     * @brief Interface for the game
     * @attention Need to have a extern "C" create(), destroy() and getType() function
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
         * @brief Destructor
         */
        virtual ~IGame() = default;

        /**
         * @brief Initialize the game
         */
        virtual void init(const std::string &name) = 0;
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
         * @return List of DrawObject to draw
         */
        virtual std::list<DrawObject *> draw() = 0;

        /**
         * @brief Get the score of the game
         * @return The score of the game
         */
        [[nodiscard]] virtual uint64_t getScore() const = 0;
    };
}

#endif //ARCADE_IGAME_HPP
