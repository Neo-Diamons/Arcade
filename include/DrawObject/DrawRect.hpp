/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DrawRect
*/

#ifndef DRAWRECT_HPP
#define DRAWRECT_HPP

#include "DrawObject.hpp"

#include "../Color.hpp"

namespace arc {
    /**
     * @brief Class for the rectangle
     */
    class DrawRect final : public DrawObject {
    public:
        int x;
        int y;
        int width;
        int height;
        Color color;

        /**
         * @brief Constructor for the rectangle
         * @param x X position of the rectangle
         * @param y Y position of the rectangle
         * @param width Width of the rectangle
         * @param height Height of the rectangle
         * @param color Color of the rectangle
         */
        DrawRect(const int x, const int y, const int width, const int height, const Color &color)
            : DrawObject(RECT), x(x), y(y), width(width), height(height), color(color) {}
    };
}

#endif //DRAWRECT_HPP
