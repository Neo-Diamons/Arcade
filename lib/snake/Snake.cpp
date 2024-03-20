/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#include <ctime>
#include <algorithm>
#include "Snake.hpp"

#include <iostream>

extern "C"
{
    arc::IGame *create()
    {
        return new arc::Snake();
    }

    void destroy(const arc::IGame *ptr)
    {
        delete ptr;
    }
}

void arc::Snake::init(const std::string &name)
{
    _name = name;
}

void arc::Snake::stop()
{

}

void arc::Snake::event(IKey *key)
{
    if (key->isKeyPressed(IKey::Z))
        _orientation = {0, -1};
    if (key->isKeyPressed(IKey::S))
        _orientation = {0, 1};
    if (key->isKeyPressed(IKey::Q))
        _orientation = {-1, 0};
    if (key->isKeyPressed(IKey::D))
        _orientation = {1, 0};
}

void arc::Snake::update()
{
    if (clock() - _lastUpdate < 250000)
        return;
    _lastUpdate = clock();

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

    if (next == _food) {
        _snake.push_back(_snake.back());
        _food = {std::rand() % WIDTH, std::rand() % HEIGHT};
    }
}

void arc::Snake::draw(IGraphical &graphical)
{
    graphical.drawText(10, 0, "Player: " + _name, WHITE);
    graphical.drawText(200, 0, "Score: " + std::to_string(_snake.size() - 4), WHITE);

    for (uint16_t x = 0; x < WIDTH; x++)
        for (uint16_t y = 0; y < HEIGHT; y++)
            graphical.drawFillRect(x * 40, y * 40 + 10, 40, 40,
                                   (x + y) % 2 ? Color(170, 215, 81) : Color(162, 209, 73));

    graphical.drawFillRect(_food.first * 40, _food.second * 40 + 10, 40, 40, Color(255, 0, 0));

    for (auto &[fst, snd] : _snake)
        graphical.drawFillRect(fst * 40, snd * 40 + 10, 40, 40, Color(71, 117, 235));

    if (_state == LOSE)
        graphical.drawTexture(200, 155, _loseTexture, 400, 90);
}

uint64_t arc::Snake::getScore() const
{
    std::cerr << "Score: " << _snake.size() - 4 << std::endl;
    return _snake.size() - 4;
}
