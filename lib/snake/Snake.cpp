/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#include "Snake.hpp"

#include <algorithm>

#include "include/DrawObject/DrawFillRect.hpp"
#include "include/DrawObject/DrawTexture.hpp"
#include "include/DrawObject/DrawText.hpp"
#include "include/LibraryType.h"

extern "C" {
    arc::IGame *create()
    {
        return new arc::Snake();
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

void arc::Snake::init(const std::string &name)
{
    _name = name;
}

void arc::Snake::stop()
{}

void arc::Snake::event(IKey *key)
{
    if (key->isKeyPressed(IKey::D))
        _orientation = {-_orientation.second, _orientation.first};
    if (key->isKeyPressed(IKey::Q))
        _orientation = {_orientation.second, -_orientation.first};
}

void arc::Snake::update()
{
    if (_state == LOSE)
        return;
    auto head = _snake.front();
    const auto next = std::make_pair(head.first + _orientation.first, head.second + _orientation.second);

    if (next.first < 0 || next.first >= WIDTH || next.second < 0 || next.second >= HEIGHT
        || std::ranges::find(_snake, next) != _snake.end()) {
        _state = LOSE;
        return;
    }

    _snake.push_front(next);
    _snake.pop_back();

    if (next == _food && _snake.size() < WIDTH * HEIGHT) {
        _snake.push_back(_snake.back());
        while (std::ranges::find(_snake, _food) != _snake.end())
            _food = {std::rand() % WIDTH, std::rand() % HEIGHT};
    }
}

std::list<arc::DrawObject *> arc::Snake::draw()
{
    std::list<DrawObject *> objects;

    objects.push_back(new DrawText(10, 0, "Player: " + _name, WHITE));
    objects.push_back(new DrawText(200, 0, "Score: " + std::to_string(getScore()), WHITE));

    for (uint16_t x = 0; x < WIDTH; x++)
        for (uint16_t y = 0; y < HEIGHT; y++)
            objects.push_back(new DrawFillRect(x * 40, y * 40 + 10, 40, 40,
                                               (x + y) % 2 ? Color(170, 215, 81) : Color(162, 209, 73)));

    objects.push_back(new DrawFillRect(_food.first * 40, _food.second * 40 + 10, 40, 40, Color(255, 0, 0)));
    for (auto &[fst, snd] : _snake)
        objects.push_back(new DrawFillRect(fst * 40, snd * 40 + 10, 40, 40, Color(71, 117, 235)));

    if (_state == LOSE)
        objects.push_back(new DrawTexture(200, 340, 400, 180, _loseTexture));
    return objects;
}

uint64_t arc::Snake::getScore() const
{
    return (_snake.size() - 4) * 100;
}
