/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

extern "C" arc::IGraphical *entryPoint()
{
    return new arc::Ncurses();
}

void arc::Ncurses::init(uint32_t width, uint32_t height)
{
    _width = width / NCURSES_RATIO;
    _height = height / NCURSES_RATIO;

    initscr();
    refresh();

    _window = newwin((int)_width, (int)_height, LINES / 2 - _height / 4, COLS / 2 - _width / 2);
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

    init_pair(BLACK,    COLOR_BLACK,    COLOR_BLACK);
    init_pair(RED,      COLOR_RED,      COLOR_BLACK);
    init_pair(GREEN,    COLOR_GREEN,    COLOR_BLACK);
    init_pair(YELLOW,   COLOR_YELLOW,   COLOR_BLACK);
    init_pair(BLUE,     COLOR_BLUE,     COLOR_BLACK);
    init_pair(MAGENTA,  COLOR_MAGENTA,  COLOR_BLACK);
    init_pair(CYAN,     COLOR_CYAN,     COLOR_BLACK);
    init_pair(WHITE,    COLOR_WHITE,    COLOR_BLACK);

    init_pair(BLOCK_BLACK,      COLOR_BLACK,    COLOR_BLACK);
    init_pair(BLOCK_RED,        COLOR_RED,      COLOR_RED);
    init_pair(BLOCK_GREEN,      COLOR_GREEN,    COLOR_GREEN);
    init_pair(BLOCK_YELLOW,     COLOR_YELLOW,   COLOR_YELLOW);
    init_pair(BLOCK_BLUE,       COLOR_BLUE,     COLOR_BLUE);
    init_pair(BLOCK_MAGENTA,    COLOR_MAGENTA,  COLOR_MAGENTA);
    init_pair(BLOCK_CYAN,       COLOR_CYAN,     COLOR_CYAN);
    init_pair(BLOCK_WHITE,      COLOR_WHITE,    COLOR_WHITE);
}

void arc::Ncurses::stop()
{
    delwin(_window);
    endwin();
    _isOpen = false;
}

void arc::Ncurses::clear()
{
    werase(_window);
    drawFillRect(0, 0, _width * NCURSES_RATIO, _height * NCURSES_RATIO, BLACK);
}

void arc::Ncurses::display()
{
    wrefresh(_window);
}

bool arc::Ncurses::isOpen()
{
    return _isOpen;
}

void arc::Ncurses::drawText(int x, int y, const std::string &text, const arc::Color &color)
{
    wattron(_window, COLOR_PAIR(color));
    mvwprintw(_window, y / NCURSES_RATIO, x / NCURSES_RATIO, text.c_str());
    wattroff(_window, COLOR_PAIR(color));
}

void arc::Ncurses::drawRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color)
{
    x /= NCURSES_RATIO;
    y /= NCURSES_RATIO * 2;
    width /= NCURSES_RATIO;
    height /= NCURSES_RATIO * 2;

    wattron(_window, COLOR_PAIR(color + 8));
    mvwhline(_window, y,              x,             0, width);
    mvwhline(_window, y,              x,             0, height);
    mvwhline(_window, y + height - 1, x,             0, width);
    mvwhline(_window, y,              x + width - 1, 0, height);
    wattroff(_window, COLOR_PAIR(color + 8));
}

void arc::Ncurses::drawFillRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color)
{
    x /= NCURSES_RATIO;
    y /= NCURSES_RATIO * 2;
    width /= NCURSES_RATIO;
    height /= NCURSES_RATIO * 2;

    wattron(_window, COLOR_PAIR(color + 8));
    for (uint32_t i = 0; i < height; i++)
        mvwhline(_window, y + i, x, 0, width);
    wattroff(_window, COLOR_PAIR(color + 8));
}

void arc::Ncurses::drawTexture(int x, int y, const arc::Texture &texture, uint32_t width, uint32_t height)
{
    x /= NCURSES_RATIO;
    y /= NCURSES_RATIO * 2;
    width /= NCURSES_RATIO;
    height /= NCURSES_RATIO * 2;

    wattron(_window, COLOR_PAIR(texture.GetColor()));
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++)
            mvwaddch(_window, y + i, x + j,
                     texture.GetPattern().c_str()[((i * width) + j) % texture.GetPattern().size()]);
    }
    wattroff(_window, COLOR_PAIR(texture.GetColor()));
}

arc::IKey *arc::Ncurses::getKey()
{
    return &_key;
}
