/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NcursesKey
*/

#include "NcursesKey.hpp"

bool arc::NcursesKey::isKeyPressed(KeyEnum key) {
    return getch() == _keyMap.at(key);
}
