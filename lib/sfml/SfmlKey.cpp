/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLKey
*/

#include "SfmlKey.hpp"
#include <iostream>

void arc::SfmlKey::setKeyPressed(sf::Keyboard::Key key)
{
    std::cout << "Key pressed: " << key << std::endl;
    _lastKeyPressed = key;
}

bool arc::SfmlKey::isKeyPressed(KeyEnum key)
{
    return _keyMap.find(key)->second == _lastKeyPressed;
}

void arc::SfmlKey::resetKey() {
    _lastKeyPressed = UNKNOWN;
}
