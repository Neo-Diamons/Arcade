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

    _graphical->init();
}

void arc::Core::run()
{
    while (_graphical->isOpen()) {

        if (_game == nullptr) {
            selectionLoop();
        } else {
            _game->event();
            _game->update();

            _graphical->clear();
            _game->draw(*_graphical);
        }

        _graphical->display();
    }
}

void arc::Core::selectionLoop()
{
}
