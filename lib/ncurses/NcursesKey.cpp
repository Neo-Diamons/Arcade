/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NcursesKey
*/

#include "NcursesKey.hpp"

bool arc::NcursesKey::isKeyPressed(KeyEnum key)
{
    int ch = getch();

    if (ch == ERR)
        ch = _lastKeyPressed;
    if (ch == UNKNOWN)
        return false;
    _lastKeyPressed = ch == _keyMap.at(key) ? UNKNOWN : ch;
    return _lastKeyPressed == UNKNOWN;
}
