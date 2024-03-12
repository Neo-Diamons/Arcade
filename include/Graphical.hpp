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

namespace arc {
    /**
     * @brief Interface for the graphical library
     */
    class Graphical {
    public:
        /**
         * @brief Exception for the graphical library
         */
        class GraphicalException : public Exception {
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
        virtual void drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color &color) = 0;

        /**
         * @brief Draw a texture on the screen
         */
        virtual void drawTexture(int x, int y, const Texture &texture, uint32_t width, uint32_t height) = 0;

        /**
         * @brief Interface for the keyboard management
         */
        class Key {
        public:
            /**
             * @brief Enum for the key
             */
            enum KeyEnum {
                UNKNOWN = -1,
                A = 0,
                B = 1,
                C = 2,
                D = 3,
                E = 4,
                F = 5,
                G = 6,
                H = 7,
                I = 8,
                J = 9,
                K = 10,
                L = 11,
                M = 12,
                N = 13,
                O = 14,
                P = 15,
                Q = 16,
                R = 17,
                S = 18,
                T = 19,
                U = 20,
                V = 21,
                W = 22,
                X = 23,
                Y = 24,
                Z = 25,
                NUM0 = 26,
                NUM1 = 27,
                NUM2 = 28,
                NUM3 = 29,
                NUM4 = 30,
                NUM5 = 31,
                NUM6 = 32,
                NUM7 = 33,
                NUM8 = 34,
                NUM9 = 35,
                ESCAPE = 36,
                LCONTROL = 37,
                LSHIFT = 38,
                LALT = 39,
                LSYSTEM = 40,
                RCONTROL = 41,
                RSHIFT = 42,
                RALT = 43,
                RSYSTEM = 44,
                MENU = 45,
                LBRACKET = 46,
                RBRACKET = 47,
                SEMICOLON = 48,
                COMMA = 49,
                PERIOD = 50,
                QUOTE = 51,
                SLASH = 52,
                BACKSLASH = 53,
                TILDE = 54,
                EQUAL = 55,
                DASH = 56,
                SPACE = 57,
                RETURN = 58,
                BACKSPACE = 59,
                TAB = 60,
                PAGEUP = 61,
                PAGEDOWN = 62,
                END = 63,
                HOME = 64,
                INSERT = 65,
                DELETE = 66,
                ADD = 67,
                SUBTRACT = 68,
                MULTIPLY = 69,
                DIVIDE = 70,
                LEFT = 71,
                RIGHT = 72,
                UP = 73,
            };

            /**
             * @brief Check if a key is pressed
             * @param key The key to check
             * @return true if the key is pressed, false otherwise
             */
            virtual bool isKeyPressed(KeyEnum key) = 0;
        };
    };
}

#endif //GRAPHICAL_HPP
