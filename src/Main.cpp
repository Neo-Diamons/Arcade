/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Main.cpp
*/

#include <iostream>

#include "Core.hpp"

void help()
{
    std::cerr << "Usage: ./arcade [path_to_graphical_library]" << std::endl;
    std::cerr << "       ./arcade [path_to_graphical_library] -s [width] [height]" << std::endl;
}

int main(const int ac, const char **av)
{
    try {
        switch (ac) {
        case 2:
            {
                arc::Core core(av[1]);
                core.run();
                break;
            }
        case 5:
            {
                if (std::string(av[2]) != "-s" && std::string(av[2]) != "--size") {
                    help();
                    return 84;
                }
                arc::Core core(av[1], std::stoi(av[3]), std::stoi(av[4]));
                core.run();
                break;
            }
        default:
            help();
            return std::string(av[1]) == "-h" || std::string(av[1]) == "--help" ? 0 : 84;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
