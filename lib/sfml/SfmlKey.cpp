/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLKey
*/

#include "SfmlKey.hpp"

void arc::SfmlKey::setKeyPressed(sf::Keyboard::Key key)
{
    _lastKeyPressed = key;
}

bool arc::SfmlKey::isKeyPressed(KeyEnum key)
{
    return _keyMap.find(key)->second == _lastKeyPressed;
}

void arc::SfmlKey::resetKey() {
    _lastKeyPressed = UNKNOWN;
}
