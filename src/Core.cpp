/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include "Core.hpp"

#include <dlfcn.h>

arc::Core::Core(const std::string &path)
{
    loadGraphicalLib(path);
}

void arc::Core::loadGraphicalLib(const std::string &path)
{
    _graphicalLib = dlopen(path.c_str(), RTLD_LAZY);
    if (!_graphicalLib)
        throw CoreException(dlerror());

    void *entryPoint = dlsym(_graphicalLib, "entryPoint");
    if (!entryPoint)
        throw CoreException(dlerror());
    _graphical = reinterpret_cast<Graphical *(*)()>(entryPoint)();
}

void arc::Core::run()
{
    while (true) {
        if (!_graphical->isOpen())
            break;

        _graphical->clear();
//        _game->event();
//        _game->update();
//        _game->draw();
        _graphical->display();
    }
}
