/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#include "Core.hpp"

#include <iostream>
#include <dirent.h>

arc::Core::Core(const std::string &path)
{
    loadGraphicalLib(path);
}

arc::Core::~Core()
{
    try {
        if (_graphical != nullptr) {
            if (_graphical->isOpen())
                _graphical->stop();
            _graphicalLoader.destroyInstance(_graphical);
        }
        if (_game != nullptr) {
            _game->stop();
            _gameLoader.destroyInstance(_game);
        }
    } catch (const DLLoader<IGraphical>::DLLoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    } catch (const DLLoader<IGame>::DLLoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

void arc::Core::loadGraphicalLib(const std::string &path)
{
    try {
        if (_graphical != nullptr) {
            _graphical->stop();
            _graphicalLoader.destroyInstance(_graphical);
        }
        _graphical = _graphicalLoader.getInstance(path);
    } catch (const DLLoader<IGraphical>::DLLoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _graphical->init(800, 800);
    _key = _graphical->getKey();
}

void arc::Core::loadGameLib(const std::string &path)
{
    try {
        if (_game != nullptr) {
            _game->stop();
            _gameLoader.destroyInstance(_game);
        }
        _game = _gameLoader.getInstance(path);
    } catch (const DLLoader<IGame>::DLLoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _game->init();
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
    closedir(pDir);
}

void arc::Core::globalAction()
{
    if (!_graphicalLibs.empty()) {
        if (_key->isKeyPressed(IKey::RIGHT)) {
            _graphicalIndex = (_graphicalIndex - 1) % _graphicalLibs.size();
            loadGraphicalLib("lib/" + _graphicalLibs[_graphicalIndex]);
        }
        if (_key->isKeyPressed(IKey::LEFT)) {
            _graphicalIndex = (_graphicalIndex + 1) % _graphicalLibs.size();
            loadGraphicalLib("lib/" + _graphicalLibs[_graphicalIndex]);
        }
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

        if (_key->isKeyPressed(IKey::RETURN) && !_gameLibs.empty()) {
            loadGameLib("lib/" + _gameLibs[_gameIndex]);
        }

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
    uint16_t offsetX = (800 - 310) / 2;
    uint16_t offsetY = (400 - 110 - _graphicalLibs.size() - _gameLibs.size()) / 2;
    _graphical->drawText(offsetX, 10 + offsetY, "/-----------Arcade------------\\", WHITE);
    _graphical->drawText(offsetX + 10, 30 + offsetY, "  Player: " + _name           , WHITE);
    _graphical->drawText(offsetX, 50 + offsetY, "|-+--   -  Graphical  -   --+-|" , WHITE);
    for (uint8_t i = 0; i < (uint8_t)_graphicalLibs.size(); i++, offsetY += 10)
        _graphical->drawText(offsetX, 70 + offsetY,
                             (i == _graphicalIndex ? "  > " : "    ") + _graphicalLibs[i] , WHITE);
    _graphical->drawText(offsetX, 80 + offsetY, "|-+--   -    Game     -   --+-|" , WHITE);
    for (uint8_t i = 0; i < (uint8_t)_gameLibs.size(); i++, offsetY += 10)
        _graphical->drawText(offsetX, 100 + offsetY,
                             (i == _gameIndex ? "  > " : "    ") + _gameLibs[i] , WHITE);
    _graphical->drawText(offsetX, 110 + offsetY, "\\-----------------------------/", WHITE);
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
