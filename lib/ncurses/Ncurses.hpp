/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#ifndef ARCADE_NCURSES_HPP
#define ARCADE_NCURSES_HPP

#include "include/Graphical.hpp"

namespace arc {
    /**
     * @brief Ncurses implementation of the graphical library
     */
    class Ncurses : public arc::Graphical {
    private:
        enum BLOCK_COLOR {
            BLOCK_BLACK = 8,
            BLOCK_RED = 9,
            BLOCK_GREEN = 10,
            BLOCK_YELLOW = 11,
            BLOCK_BLUE = 12,
            BLOCK_MAGENTA = 13,
            BLOCK_CYAN = 14,
            BLOCK_WHITE = 15
        };

    public:
        /**
         * @brief Exception implementation for the Ncurses library
         */
        class NcursesException : public GraphicalException {
        public:
            explicit NcursesException(const std::string &message) : GraphicalException("Ncurses", message) {}
        };

        void init() override;
        void stop() override;
        void clear() override;
        void display() override;

        void drawText(int x, int y, const std::string &text, const Color &color) override;
        void drawLine(int x1, int y1, int x2, int y2, const Color &color) override;
        void drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color) override;

        void drawFillRect(int x, int y, int width, int height, const Color &color) override;
//        void drawSprite(int x, int y, const std::string &path, uint32_t width, uint32_t height) override;
    };
}



#endif //ARCADE_NCURSES_HPP
