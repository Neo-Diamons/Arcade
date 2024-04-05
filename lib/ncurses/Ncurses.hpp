/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#ifndef ARCADE_NCURSES_HPP
#define ARCADE_NCURSES_HPP

#include "include/IGraphical.hpp"
#include "NcursesKey.hpp"

#include <ncurses.h>
#include <list>

namespace arc {
    /**
     * @brief Ncurses implementation of the graphical library
     */
    class Ncurses final : public IGraphical {
    private:
        std::list<std::pair<short, Color>> _colorList;
        std::list<std::pair<short, Color>> _colorBlockList;

        NcursesKey _key;
        bool _isOpen = true;

        uint32_t _width = 0;
        uint32_t _height = 0;

        WINDOW *_window = nullptr;
        const uint16_t NCURSES_RATIO = 10;

        short _getColor(const Color &color);
        short _getBlockColor(const Color &color);

        uint64_t _fpsStartTime = 0;

    public:
        /**
         * @brief Exception implementation for the Ncurses library
         */
        class NcursesException final : public GraphicalException {
        public:
            explicit NcursesException(const std::string &message) : GraphicalException("Ncurses", message) {}
        };

        void init(uint32_t width, uint32_t height) override;
        void stop() override;
        void clear() override;
        void display() override;

        bool isOpen() override;

        void drawText(int x, int y, const std::string &text, const Color &color) override;
        void drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color) override;

        void drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color &color) override;
        void drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture) override;

        IKey *getKey() override;
    };
}

#endif //ARCADE_NCURSES_HPP
