/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DrawTexture
*/

#ifndef DRAWTEXTURE_HPP
#define DRAWTEXTURE_HPP

#include "DrawObject.hpp"
#include "../Texture.hpp"

namespace arc {
    /**
     * @brief Class for the texture
     */
    class DrawTexture final : public DrawObject  {
    public:
        int x;
        int y;
        int width;
        int height;
		Texture texture;

        /**
         * @brief Constructor for the texture
         * @param x X position of the texture
         * @param y Y position of the texture
         * @param texture Texture to display
         * @param width Width of the texture
         * @param height Height of the texture
         */
        DrawTexture(const int x, const int y, const int width, const int height, const Texture &texture)
            : DrawObject(TEXTURE), x(x), y(y), width(width), height(height), texture(texture) {}
    };
}

#endif //DRAWTEXTURE_HPP
