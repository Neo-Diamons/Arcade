/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

#include "include/DrawObject/DrawFillRect.hpp"
#include "include/DrawObject/DrawTexture.hpp"
#include "include/DrawObject/DrawText.hpp"
#include "include/LibraryType.hpp"

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
    const std::vector<std::string>& map = maps[_level];

    for (size_t y = 0; y < map.size(); y++) {
        const std::string& row = map[y];

        for (size_t x = 0; x < row.size(); x++) {
            char c = row[x];

            if (c == 'o')
                _wall.emplace_back(x, y);
            if (c == '+')
                _food.emplace_back(x, y);
        }
    }
}

void arc::Nibbler::stop()
{}

void arc::Nibbler::event(IKey *key)
{
    auto head = _Nibbler.front();

    if (key->isKeyPressed(IKey::D) && !isWall({head.first + (-_orientation.second), head.second +_orientation.first}) && !isSelf({head.first + (-_orientation.second), head.second +_orientation.first}))
        _orientation = {-_orientation.second, _orientation.first};
    if (key->isKeyPressed(IKey::Q) && !isWall({head.first +  _orientation.second, head.second + (-_orientation.first)}) && !isSelf({head.first +  _orientation.second, head.second + (-_orientation.first)}))
        _orientation = {_orientation.second, -_orientation.first};
}

bool arc::Nibbler::isWall(const std::pair<uint16_t, uint16_t> &pos)
{
    return std::ranges::find(_wall, pos) != _wall.end();
}

bool arc::Nibbler::isSelf(const std::pair<int, int> &next)
{
    return std::ranges::find(_Nibbler, next) != _Nibbler.end();
}

void arc::Nibbler::update()
{
    if (_state == LOSE || _state == WIN)
        return;
    static uint64_t lastUpdate = 0;
    if (lastUpdate++ % 10)
        return;

    auto head = _Nibbler.front();
    std::pair<int, int> next = std::make_pair(head.first + _orientation.first, head.second + _orientation.second);

    if (std::ranges::find(_Nibbler, next) != _Nibbler.end()) {
        _state = LOSE;
        return;
    }

    if (!isWall(next)) {
        _Nibbler.push_front(next);
        _Nibbler.pop_back();
    } else {
        std::vector<std::pair<int, int>> newOrientations = {
                {_orientation.first, _orientation.second},
                {-_orientation.first, -_orientation.second},
                {_orientation.second, -_orientation.first},
                {-_orientation.second, _orientation.first}
        };

        bool canMoveLeft = !isWall({head.first + newOrientations[2].first, head.second + newOrientations[2].second}) &&
                           !isSelf({head.first + newOrientations[2].first, head.second + newOrientations[2].second});
        bool canMoveRight = !isWall({head.first + newOrientations[3].first, head.second + newOrientations[3].second}) &&
                            !isSelf({head.first + newOrientations[3].first, head.second + newOrientations[3].second});

        if (!canMoveLeft || !canMoveRight) {
            for (const auto& newOrientation : newOrientations) {
                next = std::make_pair(head.first + newOrientation.first, head.second + newOrientation.second);
                if (!isWall(next) && !isSelf(next)) {
                    _orientation = newOrientation;
                    break;
                }
            }
        }
    }

    for (auto &[fst, snd] : _food) {
        if (fst == head.first && snd == head.second && _Nibbler.size() < WIDTH * HEIGHT) {
            _food.remove({fst, snd});
            _Nibbler.push_back(_Nibbler.back());
            break;
        }
    }

    if (_food.empty()) {
        _level++;
        if (_level >= maps.size())
            _state = WIN;
        else
            reset();
    }
}

std::list<arc::DrawObject *> arc::Nibbler::draw()
{
    std::list<DrawObject *> objects;

    objects.push_back(new DrawText(10, 0, "Player: " + _name, WHITE));
    objects.push_back(new DrawText(200, 0, "Score: " + std::to_string(getScore()), WHITE));
    objects.push_back(new DrawText(310, 0, "Level: " + std::to_string(_level + 1), WHITE));

    for (uint16_t x = 0; x < WIDTH; x++)
        for (uint16_t y = 0; y < HEIGHT; y++)
            objects.push_back(new DrawFillRect(x * 40, y * 40 + 10, 40, 40,
                                               (x + y) % 2 ? Color(170, 215, 81) : Color(162, 209, 73)));

    objects.push_back(new DrawFillRect(0 * 40, 0 * 40 + 10, 40, 40, Color(71, 255, 235)));

    for (auto &[fst, snd] : _wall)
        objects.push_back(new DrawFillRect(fst * 40, snd * 40 + 10, 40, 40, Color(40, 55, 71)));
    for (auto &[fst, snd] : _food)
        objects.push_back(new DrawFillRect(fst * 40, snd * 40 + 10, 40, 40, Color(255, 0, 0)));
    for (auto nibbler : _Nibbler)
        objects.push_back(new DrawFillRect(nibbler.first * 40, nibbler.second * 40 + 10, 40, 40, _Nibbler.front() == nibbler ? Color(26, 82, 118) : Color(21, 117, 235)));

    if (_state == LOSE)
        objects.push_back(new DrawTexture(200, 340, 400, 180, _loseTexture));
    if (_state == WIN)
        objects.push_back(new DrawTexture(200, 340, 400, 180, _winTexture));
    return objects;
}

uint64_t arc::Nibbler::getScore() const
{
    return (_Nibbler.size() - 4) * 100;
}

void arc::Nibbler::reset() {
    _state = PLAYING;
    _Nibbler = {
        {6 + WIDTH / 2, 8 + HEIGHT / 2},
        {7 + WIDTH / 2, 8 + HEIGHT / 2},
        {8 + WIDTH / 2, 8 + HEIGHT / 2},
        {9 + WIDTH / 2, 8 + HEIGHT / 2},
    };
    _food.clear();
    _wall.clear();
    _orientation = {-1, 0};
    init(_name);
}
