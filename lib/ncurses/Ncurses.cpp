/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

#include <ncurses.h>

extern "C" arc::Graphical *entryPoint()
{
    return new arc::Ncurses();
}

void arc::Ncurses::init()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    if (has_colors() == FALSE) {
        endwin();
        throw NcursesException("terminal does not support color");
    }

    start_color();
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);

    init_pair(BLOCK_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(BLOCK_RED, COLOR_RED, COLOR_RED);
    init_pair(BLOCK_GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(BLOCK_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(BLOCK_BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(BLOCK_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(BLOCK_CYAN, COLOR_CYAN, COLOR_CYAN);
    init_pair(BLOCK_WHITE, COLOR_WHITE, COLOR_WHITE);
}

void arc::Ncurses::stop()
{
    endwin();
}

void arc::Ncurses::clear()
{
    erase();
}

void arc::Ncurses::display()
{
    refresh();
}

bool arc::Ncurses::isOpen()
{
    return true;
}

void arc::Ncurses::drawText(int x, int y, const std::string &text, const arc::Color &color)
{
    attron(COLOR_PAIR(color));
    mvprintw(y, x, text.c_str());
    attroff(COLOR_PAIR(color));
}

void arc::Ncurses::drawLine(int x1, int y1, int x2, int y2, const arc::Color &color)
{
    (void)y2;

    attron(COLOR_PAIR(color + 8));
    mvhline(y1, x1, 0, x2 - x1);
    attroff(COLOR_PAIR(color + 8));
}

void arc::Ncurses::drawRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color)
{
    attron(COLOR_PAIR(color + 8));
    mvhline(y,              x,             0, width);
    mvvline(y,              x,             0, height);
    mvhline(y + height - 1, x,             0, width);
    mvvline(y,              x + width - 1, 0, height);
    attroff(COLOR_PAIR(color + 8));
}

void arc::Ncurses::drawFillRect(int x, int y, int width, int height, const arc::Color &color)
{
    attron(COLOR_PAIR(color + 8));
    for (int i = 0; i < height; i++)
        mvhline(y + i, x, 0, width);
    attroff(COLOR_PAIR(color + 8));
}
