/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

#include <cstring>
#include <cmath>

#include "include/LibraryType.hpp"

#include <unistd.h>
#include <chrono>

extern "C" {
    arc::IGraphical *create()
    {
        return new arc::Ncurses();
    }

    void destroy(const arc::IGraphical *ptr)
    {
        delete ptr;
    }

    arc::LibraryType getType()
    {
        return arc::LibraryType::GRAPHICAL;
    }
}

short arc::Ncurses::_getColor(const Color &color)
{
    short index = -1;
    for (const auto &[fst, snd] : _colorList)
        if (snd == color)
            index = fst;
    if (index == -1) {
        index = static_cast<short>(_colorList.size() + _colorBlockList.size() + 8);
        init_color(index, static_cast<short>(color.r * 3), static_cast<short>(color.g * 3),
                   static_cast<short>(color.b * 3));
        init_pair(index, index, COLOR_BLACK);
        _colorList.emplace_back(index, color);
    }
    return index;
}

short arc::Ncurses::_getBlockColor(const Color &color)
{
    short index = -1;
    for (const auto &[fst, snd] : _colorBlockList)
        if (snd == color)
            index = fst;
    if (index == -1) {
        index = static_cast<short>(_colorList.size() + _colorBlockList.size() + 8);
        init_color(index, static_cast<short>(color.r * 3), static_cast<short>(color.g * 3),
                   static_cast<short>(color.b * 3));
        init_pair(index, index, index);
        _colorBlockList.emplace_back(index, color);
    }
    return index;
}

void arc::Ncurses::init(uint32_t width, uint32_t height)
{
    _width = width / NCURSES_RATIO;
    _height = height / NCURSES_RATIO;

    initscr();
    refresh();

    _window = newwin(static_cast<int>(_width), static_cast<int>(_height),
                     static_cast<int>(LINES / 2 - _height / 4), static_cast<int>(COLS / 2 - _width / 2));
    wrefresh(_window);

    noecho();
    curs_set(0);
    set_escdelay(0);
    keypad(stdscr, TRUE);
    set_escdelay(0);
    nodelay(stdscr, TRUE);

    if (has_colors() == FALSE) {
        endwin();
        throw NcursesException("terminal does not support color");
    }

    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);

    _fpsStartTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).
        count();
}

void arc::Ncurses::stop()
{
    delwin(_window);
    refresh();
    endwin();
    _isOpen = false;
    _window = nullptr;
}

void arc::Ncurses::clear()
{
    werase(_window);
    drawFillRect(0, 0, _width * NCURSES_RATIO, _height * NCURSES_RATIO, Color(0, 0, 0));
}

void arc::Ncurses::display()
{
    wrefresh(_window);

    const uint64_t fpsEndTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).
        count();
    const uint64_t fps = (fpsEndTime - _fpsStartTime) * 1000 / std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    usleep(1000000 / 60 - fps);
    _fpsStartTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).
        count();
}

bool arc::Ncurses::isOpen()
{
    return _isOpen;
}

void arc::Ncurses::drawText(int x, int y, const std::string &text, const Color &color)
{
    const short index = _getColor(color);

    wattron(_window, COLOR_PAIR(index));
    mvwprintw(_window,
              static_cast<int>(round(static_cast<double>(y) / NCURSES_RATIO)),
              static_cast<int>(round(static_cast<double>(x) / NCURSES_RATIO * 2)), text.c_str());
    wattroff(_window, COLOR_PAIR(index));
}

void arc::Ncurses::drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color)
{
    const short index = _getBlockColor(color);

    x = static_cast<int>(round(static_cast<double>(x) / NCURSES_RATIO));
    y = static_cast<int>(round(static_cast<double>(y) / NCURSES_RATIO / 2));
    width = static_cast<int>(round(static_cast<double>(width) / NCURSES_RATIO));
    height = static_cast<int>(round(static_cast<double>(height) / NCURSES_RATIO / 2));

    wattron(_window, COLOR_PAIR(index));
    mvwhline(_window, y, x, 0, width);
    mvwhline(_window, y, x, 0, height);
    mvwhline(_window, y + height - 1, x, 0, width);
    mvwhline(_window, y, x + width - 1, 0, height);
    wattroff(_window, COLOR_PAIR(index));
}

void arc::Ncurses::drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color &color)
{
    const short index = _getBlockColor(color);

    x = static_cast<int>(round(static_cast<double>(x) / NCURSES_RATIO));
    y = static_cast<int>(round(static_cast<double>(y) / NCURSES_RATIO / 2));
    width = static_cast<int>(round(static_cast<double>(width) / NCURSES_RATIO));
    height = static_cast<int>(round(static_cast<double>(height) / NCURSES_RATIO / 2));

    wattron(_window, COLOR_PAIR(index));
    for (uint32_t i = 0; i < height; i++)
        mvwhline(_window, y + i, x, 0, width);
    wattroff(_window, COLOR_PAIR(index));
}

void arc::Ncurses::drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture)
{
    const short index = _getColor(texture.GetColor());

    x = static_cast<int>(round(static_cast<double>(x) / NCURSES_RATIO));
    y = static_cast<int>(round(static_cast<double>(y) / NCURSES_RATIO / 2));
    width = static_cast<int>(round(static_cast<double>(width) / NCURSES_RATIO));
    height = static_cast<int>(round(static_cast<double>(height) / NCURSES_RATIO / 2));

    wattron(_window, COLOR_PAIR(index));
    for (uint32_t i = 0; i < height; i++)
        for (uint32_t j = 0; j < width; j++)
            mvwaddch(_window, y + i, x + j,
                 texture.GetPattern().c_str()[((i * width) + j) % texture.GetPattern().size()]);
    wattroff(_window, COLOR_PAIR(index));
}

arc::IKey *arc::Ncurses::getKey()
{
    return &_key;
}
