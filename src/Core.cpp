/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include <dlfcn.h>

#include "Core.hpp"

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


    _graphical->init();
    _graphical->drawText(0, 0, "Hello World", RED);
    _graphical->display();
    _graphical->clear();
    _graphical->drawFillRect(0, 0, 30, 10, RED);
    _graphical->display();
    _graphical->stop();
}
