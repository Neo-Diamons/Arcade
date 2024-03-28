/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DrawFillRect
*/

#ifndef DRAWFILLRECT_HPP
#define DRAWFILLRECT_HPP

#include "DrawObject.hpp"

#include "../Color.hpp"

namespace arc {
    /**
     * @brief Class for the filled rectangle
     */
    class DrawFillRect final : public DrawObject {
    public:
        int x;
        int y;
        int width;
        int height;
        Color color;

        /**
         * @brief Constructor for the filled rectangle
         * @param x X position of the filled rectangle
         * @param y Y position of the filled rectangle
         * @param width Width of the filled rectangle
         * @param height Height of the filled rectangle
         * @param color Color of the filled rectangle
         */
        DrawFillRect(const int x, const int y, const int width, const int height, const Color &color)
            : DrawObject(FILLRECT), x(x), y(y), width(width), height(height), color(color) {}
    };
}

#endif //DRAWFILLRECT_HPP
