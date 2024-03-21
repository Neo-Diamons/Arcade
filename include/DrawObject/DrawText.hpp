/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DrawText
*/

#ifndef DRAWTEXT_HPP
#define DRAWTEXT_HPP

#include "DrawObject.hpp"

#include "../Color.hpp"

namespace arc {
    /**
     * @brief Class for the text
     */
    class DrawText final : public DrawObject {
    public:
        int x;
        int y;
        std::string text;
        Color color;

        /**
         * @brief Constructor for the text
         * @param x X position of the text
         * @param y Y position of the text
         * @param text Text to display
         * @param color Color of the text
         */
        DrawText(const int x, const int y, const std::string &text, const Color &color)
            : DrawObject(TEXT), x(x), y(y), text(text), color(color) {}
    };
}

#endif //DRAWTEXT_HPP
