/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLKey
*/

#include "SfmlKey.hpp"

void arc::SfmlKey::setKeyPressed(sf::Keyboard::Key key) {
    this->_lastKeyPressed = key;
}

bool arc::SfmlKey::isKeyPressed(arc::IKey::KeyEnum key) {
    return this->_keyMap.find(key)->second == this->_lastKeyPressed;
}
