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

    class Texture {
        std::string _path;
        std::string _pattern;
        Color _color;

    public:
        Texture(const std::string &path, const std::string &pattern, Color color)
            : _path(path), _pattern(pattern), _color(color) {}

        [[nodiscard]] std::string GetPath() const { return _path; }
        [[nodiscard]] std::string GetPattern() const { return _pattern; }
        [[nodiscard]] Color GetColor() const { return _color; }
    };
}

#endif //ARCADE_TEXTURE_HPP
