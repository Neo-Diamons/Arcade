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
#include "Texture.hpp"
#include "IKey.hpp"

namespace arc {
    /**
     * @interface IGraphical
     * @brief Interface for the graphical library
     * @attention Need to have a extern "C" create(), destroy() and getType() function
     */
    class IGraphical {
    public:
        /**
         * @brief Exception for the graphical library
         */
        class GraphicalException : public Exception {
        public:
            GraphicalException(const std::string &name, const std::string &message) : Exception(name, message) {}
        };

        /**
         * @brief Destructor
         */
        virtual ~IGraphical() = default;

        /**
         * @brief Initialize the graphical
         * @param width The width of the window
         * @param height The height of the window
         */
        virtual void init(uint32_t width, uint32_t height) = 0;
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
         * @brief Check if the window is open
         * @return true if the window is open, false otherwise
         */
        virtual bool isOpen() = 0;

        /**
         * @brief Draw text on the screen
         * @param x The x position of the text
         * @param y The y position of the text
         * @param text The text to draw
         * @param color The color of the text
         */
        virtual void drawText(int x, int y, const std::string &text, const Color &color) = 0;
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
        virtual void drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color &color) = 0;

        /**
         * @brief Draw a texture on the screen
         * @param x The x position of the texture
         * @param y The y position of the texture
         * @param width The width of the texture
         * @param height The height of the texture
         * @param texture The texture to draw
         */
        virtual void drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture) = 0;

        /**
         * @brief Get the keyboard management
         * @return The keyboard management
         */
        virtual IKey *getKey() = 0;
    };
}

#endif //GRAPHICAL_HPP
