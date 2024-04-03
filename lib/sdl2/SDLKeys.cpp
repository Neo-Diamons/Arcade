/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NcursesKey
*/

#include "SDLKeys.hpp"

bool arc::SDLKeys::isKeyPressed(KeyEnum key)
{
    return _event->type == SDL_KEYDOWN
        && _event->key.keysym.sym == _keyMap.at(key);
}
