/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Main.cpp
*/

#include <iostream>

#include "Core.hpp"

int main(const int ac, const char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade [path_to_graphical_library]" << std::endl;
        return 84;
    }

    try {
        arc::Core core(av[1]);
        core.run();
    } catch (const arc::Core::CoreException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
