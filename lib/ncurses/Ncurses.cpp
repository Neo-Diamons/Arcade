/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

#include <ncurses.h>
#include <csignal>

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
}

void arc::Ncurses::stop()
{
    sleep(10);

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

void arc::Ncurses::drawText(int x, int y, const std::string &text, const arc::Color &color)
{
    attron(COLOR_PAIR(color));
    mvprintw(y, x, text.c_str());
    attroff(COLOR_PAIR(color));
}

void arc::Ncurses::drawLine(int x1, int y1, int x2, int y2, const arc::Color &color)
{
    attron(COLOR_PAIR(color));
    mvhline(y1, x1, x2, y2);
    attroff(COLOR_PAIR(color));
}

void arc::Ncurses::drawRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color)
{
    attron(COLOR_PAIR(color));
    mvhline(y, x, 0, width);
    mvhline(y + height, x, 0, width);
    mvvline(y, x, 0, height);
    mvvline(y, x + width, 0, height);
    attroff(COLOR_PAIR(color));
}

void arc::Ncurses::drawFillRect(int x, int y, int width, int height, const arc::Color &color)
{
    attron(COLOR_PAIR(color));
    for (int i = 0; i < height; i++)
        mvhline(y + i, x, 0, width);
    attroff(COLOR_PAIR(color));
}
