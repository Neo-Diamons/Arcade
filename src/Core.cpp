/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include "Core.hpp"

#include <dlfcn.h>
#include <dirent.h>
#include <iostream>

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
    _graphical->init(80, 80);
    _key = _graphical->getKey();
}

void arc::Core::loadGameLib(const std::string &path)
{
    _game = reinterpret_cast<IGame *(*)()>(loadLib(path))();
    _game->init();
}

void arc::Core::globalAction()
{
    if (!_graphicalLibs.empty()) {
        if (_key->isKeyPressed(IKey::RIGHT))
            _graphicalIndex = (_graphicalIndex - 1) % _graphicalLibs.size();
        if (_key->isKeyPressed(IKey::LEFT))
            _graphicalIndex = (_graphicalIndex + 1) % _graphicalLibs.size();
    }

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

        if (!_gameLibs.empty()) {
            if (_key->isKeyPressed(IKey::UP))
                _gameIndex = (_gameIndex - 1) % _gameLibs.size();
            if (_key->isKeyPressed(IKey::DOWN))
                _gameIndex = (_gameIndex + 1) % _gameLibs.size();
        }
    }
}

void arc::Core::selectionLoop()
{
    if (_name.length() < 16)
        for (uint16_t i = IKey::A; i < IKey::Z; i++)
            if (_key->isKeyPressed(static_cast<IKey::KeyEnum>(i)))
                _name += static_cast<char>(i + 'A');
    if (_key->isKeyPressed(IKey::BACKSPACE) && !_name.empty())
        _name.pop_back();

    _graphical->clear();
    uint16_t offsetX = (80 - 31) / 2;
    uint16_t offsetY = (40 - 11 - _graphicalLibs.size() - _gameLibs.size()) / 2;
    _graphical->drawText(offsetX, 1 + offsetY, "/-----------Arcade------------\\", WHITE);
    _graphical->drawText(offsetX, 3 + offsetY, "  Player: " + _name           , WHITE);
    _graphical->drawText(offsetX, 5 + offsetY, "|-+--   -  Graphical  -   --+-|" , WHITE);
    for (uint8_t i = 0; i < (uint8_t)_graphicalLibs.size(); i++, offsetY++)
        _graphical->drawText(offsetX, 7 + offsetY,
                             (i == _graphicalIndex ? "  > " : "    ") + _graphicalLibs[i] , WHITE);
    _graphical->drawText(offsetX, 8 + offsetY, "|-+--   -    Game     -   --+-|" , WHITE);
    for (uint8_t i = 0; i < (uint8_t)_gameLibs.size(); i++, offsetY++)
        _graphical->drawText(offsetX, 10 + offsetY,
                             (i == _gameIndex ? "  > " : "    ") + _gameLibs[i] , WHITE);
    _graphical->drawText(offsetX, 11 + offsetY, "\\-----------------------------/", WHITE);
}

void arc::Core::run()
{
    try {
        getLib();
    } catch (const CoreException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }

    while (_graphical->isOpen()) {
        globalAction();
        if (!_graphical->isOpen())
            break;

        if (_game == nullptr) {
            selectionLoop();
        } else {
            try {
                _game->event(_key);
                _game->update();
            } catch (const IGame::GameException &e) {
                std::cerr << e.what() << std::endl;
                exit(84);
            }

            try {
                _graphical->clear();
                _game->draw(*_graphical);
            } catch (const IGraphical::GraphicalException &e) {
                std::cerr << e.what() << std::endl;
                exit(84);
            }
        }
        _graphical->display();
    }
}

void arc::Core::getLib()
{
    DIR *pDir = opendir("lib");

    if (!pDir)
        throw CoreException("Can't open lib directory");
    for (struct dirent *pDirent = readdir(pDir); pDirent; pDirent = readdir(pDir)) {
        std::string name = pDirent->d_name;
        for (const auto &lib : _graphicalLibFiles)
            if (name == lib) {
                _graphicalLibs.push_back(name);
                break;
            }
        for (const auto &lib : _gameLibFiles)
            if (name == lib) {
                _gameLibs.push_back(name);
                break;
            }
    }
}
