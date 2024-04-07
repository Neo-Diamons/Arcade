/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "include/DrawObject/DrawFillRect.hpp"
#include "include/DrawObject/DrawTexture.hpp"
#include "include/DrawObject/DrawText.hpp"
#include "include/LibraryType.h"

extern "C" {
    arc::IGame *create()
    {
        return new arc::Nibbler();
    }

    void destroy(const arc::IGame *ptr)
    {
        delete ptr;
    }

    arc::LibraryType getType()
    {
        return arc::LibraryType::GAME;
    }
}

void arc::Nibbler::init(const std::string &name)
{
    _name = name;
    size_t x = 0;
    size_t y = 0;

    for (char c : _map) {
        if (c == '\n') {
            y++;
            x = 0;
            continue;
        }
        if (c == 'o')
            _wall.emplace_back(x, y);
        if (c == '+')
            _food.emplace_back(x, y);
        x++;
        if (x > WIDTH) {
            x = 0;
            y++;
        }
    }
}

void arc::Nibbler::stop()
{}

void arc::Nibbler::event(IKey *key)
{
    if (key->isKeyPressed(IKey::D))
        _orientation = {-_orientation.second, _orientation.first};
    if (key->isKeyPressed(IKey::Q))
        _orientation = {_orientation.second, -_orientation.first};
}

bool isWall(const std::pair<uint16_t, uint16_t> &pos, const std::list<std::pair<uint16_t, uint16_t>> &wall)
{
    return std::ranges::find(wall, pos) != wall.end();
}

void arc::Nibbler::update()
{
    if (_state == LOSE)
        return;
    static uint64_t lastUpdate = 0;
    if (lastUpdate++ % 10)
        return;

    auto head = _Nibbler.front();
    const auto next = std::make_pair(head.first + _orientation.first, head.second + _orientation.second);

    if (next.first < 0 || next.first >= WIDTH || next.second < 0 || next.second >= HEIGHT
        || std::ranges::find(_Nibbler, next) != _Nibbler.end()) {
        _state = LOSE;
        return;
    }

    if (!isWall(next, _wall)) {
        _Nibbler.push_front(next);
        _Nibbler.pop_back();
    } else {
        int rand = std::rand() % 2;

        if (rand == 0) {
            _orientation = {-_orientation.second, _orientation.first};
        } else {
            _orientation = {_orientation.second, -_orientation.first};
        }
    }

    for (auto &[fst, snd] : _food) {
        if (fst == head.first && snd == head.second && _Nibbler.size() < WIDTH * HEIGHT) {
            _food.remove({fst, snd});
            _Nibbler.push_back(_Nibbler.back());
            break;
        }
    }
}

std::list<arc::DrawObject *> arc::Nibbler::draw()
{
    std::list<DrawObject *> objects;

    objects.push_back(new DrawText(10, 0, "Player: " + _name, WHITE));
    objects.push_back(new DrawText(200, 0, "Score: " + std::to_string(getScore()), WHITE));

    for (uint16_t x = 0; x < WIDTH; x++)
        for (uint16_t y = 0; y < HEIGHT; y++)
            objects.push_back(new DrawFillRect(x * 40, y * 40 + 10, 40, 40,
                                               (x + y) % 2 ? Color(170, 215, 81) : Color(162, 209, 73)));

    objects.push_back(new DrawFillRect(0 * 40, 0 * 40 + 10, 40, 40, Color(71, 255, 235)));

    for (auto &[fst, snd] : _Nibbler)
        objects.push_back(new DrawFillRect(fst * 40, snd * 40 + 10, 40, 40, Color(71, 117, 235)));
    for (auto &[fst, snd] : _wall)
        objects.push_back(new DrawFillRect(fst * 40, snd * 40 + 10, 40, 40, Color(40, 55, 71)));
    for (auto &[fst, snd] : _food)
        objects.push_back(new DrawFillRect(fst * 40, snd * 40 + 10, 40, 40, Color(255, 0, 0)));

    if (_state == LOSE)
        objects.push_back(new DrawTexture(200, 340, 400, 180, _loseTexture));
    return objects;
}

uint64_t arc::Nibbler::getScore() const
{
    return (_Nibbler.size() - 4) * 100;
}
