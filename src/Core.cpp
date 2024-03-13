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
    _key = _graphical->getKey();
}

void arc::Core::run()
{
    while (_graphical->isOpen()) {
        if (_game == nullptr) {
            selectionLoop();
            if (!_graphical->isOpen())
                break;
        } else {
            _game->event(_key);
            _game->update();

            _graphical->clear();
            _game->draw(*_graphical);
        }
        _graphical->display();
    }
}

void arc::Core::selectionLoop()
{
    if (_key->isKeyPressed(Key::Q))
        _graphical->stop();
}
