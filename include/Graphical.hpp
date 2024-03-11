/**
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Graphical
*/

#ifndef GRAPHICAL_HPP
#define GRAPHICAL_HPP

#include <cstdint>

#include "Exception.hpp"

namespace arc {
    /**
     * @brief Enum for the color of the graphical elements
     */
    enum Color {
        BLACK = 0,
        RED = 1,
        GREEN = 2,
        YELLOW = 3,
        BLUE = 4,
        MAGENTA = 5,
        CYAN = 6,
        WHITE = 7
    };

    /**
     * @brief Interface for the graphical library
     */
    class Graphical {
    public:
        /**
         * @brief Exception for the graphical library
         */
        class GraphicalException : public arc::Exception {
        public:
            GraphicalException(const std::string &name, const std::string &message) : Exception(name, message) {}
        };

        /**
         * @brief Initialize the graphical library
         */
        virtual ~Graphical() = default;

        /**
         * @brief Initialize the graphical
         */
        virtual void init() = 0;
        /**
         * @brief Stop the graphical library and free the memory
         */
        virtual void stop() = 0;
        /**
         * @brief Clear the screen
         */
        virtual void clear() = 0;
        /**
         * @brief Display the screen
         */
        virtual void display() = 0;

        /**
         * @brief Draw text on the screen
         * @param x The x position of the text
         * @param y The y position of the text
         * @param text The text to draw
         * @param color The color of the text
         */
        virtual void drawText(int x, int y, const std::string &text, const Color &color) = 0;
        /**
         * @brief Draw a line on the screen
         * @param x1 The x position of the start of the line
         * @param y1 The y position of the start of the line
         * @param x2 The x position of the end of the line
         * @param y2 The y position of the end of the line
         * @param color The color of the line
         */
        virtual void drawLine(int x1, int y1, int x2, int y2, const Color &color) = 0;
        /**
         * @brief Draw a rectangle on the screen
         * @param x The x position of the rectangle
         * @param y The y position of the rectangle
         * @param width The width of the rectangle
         * @param height The height of the rectangle
         * @param color The color of the rectangle
         */
        virtual void drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color) = 0;

        /**
         * @brief Draw a filled rectangle on the screen
         * @param x The x position of the rectangle
         * @param y The y position of the rectangle
         * @param width The width of the rectangle
         * @param height The height of the rectangle
         * @param color The color of the rectangle
         */
        virtual void drawFillRect(int x, int y, int width, int height, const Color &color) = 0;
//        virtual void drawSprite(int x, int y, const std::string &path, uint32_t width, uint32_t height) = 0;
    };
}

#endif //GRAPHICAL_HPP
