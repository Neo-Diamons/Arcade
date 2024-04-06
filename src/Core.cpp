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
    try {
        getLib();
        for (uint8_t i = 0; i < static_cast<uint8_t>(_graphicalLibs.size()); i++)
            if (path.find(_graphicalLibs[i]) != std::string::npos) {
                _graphicalIndex = i;
                break;
            }

        if (_graphicalIndex == _graphicalLibs.size())
            throw CoreException("No graphical library found");
    } catch (const CoreException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }

    loadGraphicalLib(path);
}

arc::Core::~Core()
{
    try {
        if (_graphical != nullptr) {
            _graphical->stop();
            _graphicalLoader.destroyInstance(_graphical);
        }
        if (_game != nullptr) {
            _game->stop();
            _score = _game->getScore();
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
    _graphical->init(WIDTH, HEIGHT);
    _key = _graphical->getKey();
}

void arc::Core::loadGameLib(const std::string &path)
{
    try {
        if (_game != nullptr) {
            _game->stop();
            _score = _game->getScore();
            _gameLoader.destroyInstance(_game);
        }
        _game = _gameLoader.getInstance(path);
    } catch (const DLLoader<IGame>::DLLoaderException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _game->init(_name);
}

void arc::Core::getLib()
{
    DIR *pDir = opendir("lib");

    if (!pDir)
        throw CoreException("Can't open lib directory");
    for (const dirent *pDirent = readdir(pDir); pDirent; pDirent = readdir(pDir)) {
        std::string name = pDirent->d_name;
        if (name.find(".so") != name.size() - 3)
            continue;

        LibraryType type;
        try {
            type = _gameLoader.getType("lib/" + name);
        } catch (const DLLoader<IGame>::DLLoaderException &e) {
            continue;
        }

        switch (type) {
        case GRAPHICAL:
            _graphicalLibs.push_back(name);
            break;
        case GAME:
            _gameLibs.push_back(name);
            break;
        }
    }
    closedir(pDir);
}

void arc::Core::globalAction()
{
    if (!_graphicalLibs.empty() && _graphicalLibs.size() > 1) {
        if (_key->isKeyPressed(IKey::RIGHT)) {
            _graphicalIndex = (_graphicalIndex + 1) % _graphicalLibs.size();
            loadGraphicalLib("lib/" + _graphicalLibs[_graphicalIndex]);
        }
        if (_key->isKeyPressed(IKey::LEFT)) {
            _graphicalIndex = std::min<uint8_t>(_graphicalLibs.size() - 1, _graphicalIndex - 1);
            loadGraphicalLib("lib/" + _graphicalLibs[_graphicalIndex]);
        }
    }

    if (_game != nullptr) {
        if (_key->isKeyPressed(IKey::R)) {
            _game->stop();
            _score = _game->getScore();
            _gameLoader.destroyInstance(_game);
            _game = _gameLoader.getInstance("lib/" + _gameLibs[_gameIndex]);
            _game->init(_name);
        }

        if (_key->isKeyPressed(IKey::ESCAPE)) {
            _game->stop();
            _score = _game->getScore();
            _gameLoader.destroyInstance(_game);
            _game = nullptr;
        }
    } else {
        if (_key->isKeyPressed(IKey::ESCAPE))
            _graphical->stop();

        if (_key->isKeyPressed(IKey::SPACE) && !_gameLibs.empty())
            loadGameLib("lib/" + _gameLibs[_gameIndex]);

        if (!_gameLibs.empty()) {
            if (_key->isKeyPressed(IKey::UP))
                _gameIndex = std::min<uint8_t>(_gameLibs.size() - 1, _gameIndex - 1);
            if (_key->isKeyPressed(IKey::DOWN))
                _gameIndex = (_gameIndex + 1) % _gameLibs.size();
        }
    }
}

std::list<arc::DrawObject *> arc::Core::selectionLoop()
{
    if (_name.length() < 16)
        for (uint16_t i = IKey::A; i < IKey::Z; i++)
            if (_key->isKeyPressed(static_cast<IKey::KeyEnum>(i)))
                _name += static_cast<char>(i + 'A');
    if (_key->isKeyPressed(IKey::BACKSPACE) && !_name.empty())
        _name.pop_back();

    std::list<DrawObject *> objects;
    constexpr uint16_t offsetX = (800 - 310) / 4;
    uint16_t offsetY = (400 - 120) / 2 - _graphicalLibs.size() * 10 - _gameLibs.size() * 10;
    objects.push_back(new DrawText(offsetX, 10 + offsetY, "/-----------Arcade------------\\", WHITE));
    objects.push_back(new DrawText(offsetX + 10, 30 + offsetY, "  Player: " + _name, WHITE));
    objects.push_back(new DrawText(offsetX + 10, 40 + offsetY, "  Score: " + std::to_string(_score), WHITE));
    objects.push_back(new DrawText(offsetX, 60 + offsetY, "|-+--   -  Graphical  -   --+-|", WHITE));
    for (uint8_t i = 0; i < static_cast<uint8_t>(_graphicalLibs.size()); i++, offsetY += 10)
        objects.push_back(new DrawText(offsetX, 80 + offsetY,
                                       (i == _graphicalIndex ? "  > " : "    ") + _graphicalLibs[i], WHITE));
    objects.push_back(new DrawText(offsetX, 90 + offsetY, "|-+--   -    Game     -   --+-|", WHITE));
    for (uint8_t i = 0; i < static_cast<uint8_t>(_gameLibs.size()); i++, offsetY += 10)
        objects.push_back(new DrawText(offsetX, 110 + offsetY,
                                       (i == _gameIndex ? "  > " : "    ") + _gameLibs[i], WHITE));
    objects.push_back(new DrawText(offsetX, 120 + offsetY, "\\-----------------------------/", WHITE));
    return objects;
}

void arc::Core::draw(DrawObject *object) const
{
    switch (object->getType()) {
    case TEXT:
        draw(dynamic_cast<DrawText *>(object));
        break;
    case RECT:
        draw(dynamic_cast<DrawRect *>(object));
        break;
    case FILLRECT:
        draw(dynamic_cast<DrawFillRect *>(object));
        break;
    case TEXTURE:
        draw(dynamic_cast<DrawTexture *>(object));
        break;
    }
    delete object;
}

void arc::Core::draw(const DrawText *object) const
{
    _graphical->drawText(object->x, object->y, object->text, object->color);
}

void arc::Core::draw(const DrawRect *object) const
{
    _graphical->drawRect(object->x, object->y, object->width, object->height, object->color);
}

void arc::Core::draw(const DrawFillRect *object) const
{
    _graphical->drawFillRect(object->x, object->y, object->width, object->height, object->color);
}

void arc::Core::draw(const DrawTexture *object) const
{
    _graphical->drawTexture(object->x, object->y, object->width, object->height, object->texture);
}

void arc::Core::run()
{
    std::list<DrawObject *> objects;
    while (_graphical->isOpen()) {
        globalAction();
        if (!_graphical->isOpen())
            break;

        if (_game == nullptr) {
            objects = selectionLoop();
        } else {
            try {
                _game->event(_key);
                _game->update();
                objects = _game->draw();
            } catch (const IGame::GameException &e) {
                std::cerr << e.what() << std::endl;
                exit(84);
            }
        }
        try {
            _graphical->clear();
            for (const auto object : objects)
                draw(object);
            objects.clear();
            _graphical->display();
        } catch (const IGraphical::GraphicalException &e) {
            std::cerr << e.what() << std::endl;
            exit(84);
        }
    }
}
