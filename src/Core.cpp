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
    _graphical = reinterpret_cast<IGraphical *(*)()>(loadLib(path))();
    _graphical->init();
    _key = _graphical->getKey();
}

void arc::Core::loadGameLib(const std::string &path)
{
    _game = reinterpret_cast<IGame *(*)()>(loadLib(path))();
    _game->init();
}

void arc::Core::globalAction()
{
    if (_key->isKeyPressed(IKey::RIGHT))
        _graphicalIndex = (_graphicalIndex + 1) % 2;
    if (_key->isKeyPressed(IKey::LEFT))
        _graphicalIndex = (_graphicalIndex + 1) % 2;

    if (_game != nullptr) {
        if (_key->isKeyPressed(IKey::R)) {
            _game->stop();
            _game->init();
        }

        if (_key->isKeyPressed(IKey::ESCAPE)) {
            _game->stop();
            _game = nullptr;
        }
    } else {
        if (_key->isKeyPressed(IKey::ESCAPE))
            _graphical->stop();

        if (_key->isKeyPressed(IKey::UP))
            _gameIndex = (_gameIndex + 1) % 2;
        if (_key->isKeyPressed(IKey::DOWN))
            _gameIndex = (_gameIndex + 1) % 2;
    }
}

void arc::Core::selectionLoop()
{
    _graphical->drawText(2, 1, "Select a game", WHITE);
    for (uint16_t i = IKey::A; i < IKey::Z; i++)
        if (_key->isKeyPressed(static_cast<IKey::KeyEnum>(i)))
            name += static_cast<char>(i + 'A');
    _graphical->drawText(2, 3, "Player: " + name, WHITE);
}

void arc::Core::run()
{
    while (_graphical->isOpen()) {
        globalAction();
        if (!_graphical->isOpen())
            break;

        if (_game == nullptr) {
//             _graphical->clear();
            selectionLoop();
        } else {
            _game->event(_key);
            _game->update();

            _graphical->clear();
            _game->draw(*_graphical);
        }
        _graphical->display();
    }
}
