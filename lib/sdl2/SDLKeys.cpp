/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NcursesKey
*/

#include "SDLKeys.hpp"

bool arc::SDLKeys::isKeyPressed(KeyEnum key)
{
    SDL_Event event;

    return SDL_PollEvent(&event)
        && event.key.keysym.sym == _keyMap.at(key);
}
