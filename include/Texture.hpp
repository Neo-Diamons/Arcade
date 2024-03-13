/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Texture
*/

#ifndef ARCADE_TEXTURE_HPP
#define ARCADE_TEXTURE_HPP

#include <string>

#include "Color.hpp"

namespace arc {
    /**
     * @brief Class for the texture which is used to handle the textures with graphical libraries change at runtime
     */
    class Texture {
        std::string _path;
        std::string _pattern;
        Color _color;

    public:
        /**
         * @brief Constructor for the texture
         * @param path Path to the texture, use by graphical libraries (like SFML, SDL, etc.)
         * @param pattern Pattern of the texture, use by textual libraries (like Ncurses, etc.)
         * @param color Color of the texture
         */
        Texture(const std::string &path, const std::string &pattern, Color color)
            : _path(path), _pattern(pattern), _color(color) {}

        /**
         * @brief Get the path of the texture
         * @return The path of the texture
         */
        [[nodiscard]] std::string GetPath() const { return _path; }
        /**
         * @brief Get the pattern of the texture
         * @return The pattern of the texture
         */
        [[nodiscard]] std::string GetPattern() const { return _pattern; }
        /**
         * @brief Get the color of the texture
         * @return The color of the texture
         */
        [[nodiscard]] Color GetColor() const { return _color; }
    };
}

#endif //ARCADE_TEXTURE_HPP
