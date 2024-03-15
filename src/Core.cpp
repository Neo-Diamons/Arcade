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

void *arc::Core::loadLib(const std::string &path)
{
    _graphicalLib = dlopen(path.c_str(), RTLD_LAZY);
    if (!_graphicalLib)
        throw CoreException(dlerror());

    void *entryPoint = dlsym(_graphicalLib, "entryPoint");
    if (!entryPoint)
        throw CoreException(dlerror());
    return entryPoint;
}

void arc::Core::loadGraphicalLib(const std::string &path)
{
    _graphical = reinterpret_cast<Graphical *(*)()>(loadLib(path))();
    _graphical->init();
    _key = _graphical->getKey();
}

void arc::Core::loadGameLib(const std::string &path)
{
    _game = reinterpret_cast<Game *(*)()>(loadLib(path))();
    _game->init();
}

void arc::Core::globalAction()
{
    if (_key->isKeyPressed(Key::BACKSPACE))
        _graphical->stop();

    if (_key->isKeyPressed(Key::K))
        _graphical->stop();

    if (_key->isKeyPressed(Key::RIGHT))
        _graphicalIndex = (_graphicalIndex + 1) % 2;
    if (_key->isKeyPressed(Key::LEFT))
        _graphicalIndex = (_graphicalIndex + 1) % 2;

    if (_game != nullptr) {
        if (_key->isKeyPressed(Key::R)) {
            _game->stop();
            _game->init();
        }

        if (_key->isKeyPressed(Key::BACKSPACE)) {
            _game->stop();
            _game = nullptr;
        }
    } else {
        if (_key->isKeyPressed(Key::BACKSPACE))
            _graphical->stop();

        if (_key->isKeyPressed(Key::UP))
            _gameIndex = (_gameIndex + 1) % 2;
        if (_key->isKeyPressed(Key::DOWN))
            _gameIndex = (_gameIndex + 1) % 2;
    }
}

void arc::Core::run()
{
    while (_graphical->isOpen()) {
        globalAction();
        if (!_graphical->isOpen())
            break;

        else {
            _game->event(_key);
            _game->update();

            _graphical->clear();
            _game->draw(*_graphical);
        }
        _graphical->display();
    }
}
