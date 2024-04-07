/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Nibbler
*/

#ifndef ARCADE_Nibbler_HPP
#define ARCADE_Nibbler_HPP

#include <list>

#include "include/IGame.hpp"
#include "include/Texture.hpp"

namespace arc {
    /**
     * @brief Nibbler game
     */
    class Nibbler final : public IGame
    {
        const uint16_t WIDTH = 20;
        const uint16_t HEIGHT = 20;

        std::string _name;

        std::list<std::pair<int, int>> _Nibbler = {
            {6 + WIDTH / 2, 8 + HEIGHT / 2},
            {7 + WIDTH / 2, 8 + HEIGHT / 2},
            {8 + WIDTH / 2, 8 + HEIGHT / 2},
            {9 + WIDTH / 2, 8 + HEIGHT / 2},
        };

        std::pair<int, int> _orientation = {-1, 0};

        enum STATE
        {
            PLAYING,
            LOSE
        } _state = PLAYING;

        Texture _loseTexture = Texture(
            "assets/lose.png",
            "========================================"
            "                                        "
            " []        [][][][]  [][][][]  [][][][] "
            " []        []    []  []        []       "
            " []        []    []  [][][][]  [][][][] "
            " []        []    []        []  []       "
            " [][][][]  [][][][]  [][][][]  [][][][] "
            "                                        "
            "========================================",
            Color(255, 0, 0));

        std::string _map = "oooooooooooooooooooo\n"
                           "o+.+.+.+....+.+.+.+o\n"
                           "o.oooo+o+oo+o+oooo.o\n"
                           "o+o..o.o.oo.o.o..o+o\n"
                           "o+o..o.o.oo.o.o..o+o\n"
                           "o.oooo+o+oo+o+oooo.o\n"
                           "o+.+.+.+....+.+.+.+o\n"
                           "o.oooo+o+oo+o+oooo.o\n"
                           "o.oooo+o+oo+o+oooo.o\n"
                           "o+.....+....+.....+o\n"
                           "o.oooo+o+oo+o+oooo.o\n"
                           "o+o..o.o.oo.o.o..o+o\n"
                           "o.oooo+o+oo+o+oooo.o\n"
                           "o+.+.+.+....+.+.+.+o\n"
                           "o.oooo+o+oo+o+oooo.o\n"
                           "o+o..o.o.oo.o.o..o+o\n"
                           "o+o..o.o.oo.o.o..o+o\n"
                           "o.oooo+o+oo+o+oooo.o\n"
                           "o+.+.+.+....+.+.+.+o\n"
                           "oooooooooooooooooooo";
        std::list<std::pair<uint16_t, uint16_t>> _wall;
        std::list<std::pair<uint16_t, uint16_t>> _food;

    public:
        void init(const std::string &name) override;
        void stop() override;

        void event(IKey *key) override;
        void update() override;
        std::list<DrawObject *> draw() override;

        [[nodiscard]] uint64_t getScore() const override;
    };
}


#endif //ARCADE_Nibbler_HPP
