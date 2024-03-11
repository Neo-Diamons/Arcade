/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Main.cpp
*/

#include "Core.hpp"

int main(const int ac, const char **av)
{
    if (ac != 2)
        return 84;

    arc::Core core(av[1]);
    return 0;
}
