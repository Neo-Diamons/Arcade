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
#include <vector>

namespace arc {
    /**
     * @brief Nibbler game
     */
    class Nibbler final : public IGame
    {
        const uint16_t WIDTH = 20;
        const uint16_t HEIGHT = 20;

        std::string _name;
        size_t _level = 0;

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
            LOSE,
            WIN
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

        Texture _winTexture = Texture(
            "assets/win.png",
            "========================================"
            "                                        "
            " [][][][]  [][][][]  [][][][]  [][][][] "
            " []    []  []        []    []  []    [] "
            " []    []  [][][][]  [][][][]  [][][][] "
            " []    []        []  []    []  []   []  "
            " [][][][]  [][][][]  [][][][]  []    [] "
            "                                        "
            "========================================",
            Color(0, 255, 0));

        std::vector<std::vector<std::string>> maps = {
            {
                "oooooooooooooooooooo",
                "o+....+......+....+o",
                "o.oooo.oooooo.oooo.o",
                "o.o..o+o....o+o..o.o",
                "o.o..o.oooooo.o..o.o",
                "o.o..o...++...o..o.o",
                "o.o..oooooooo.o..o.o",
                "o+o.........o+o..o+o",
                "o.o..oooooooo.o..o.o",
                "o.o..o.....oo.o..o.o",
                "o.o..o.ooo....o..o.o",
                "o.o..o.o.oooooo..o.o",
                "o+o..o+o.........o+o",
                "o.o..o.oooooooo..o.o",
                "o.o..o...++...o..o.o",
                "o.o..o.oooooo.o..o.o",
                "o.o..o+o....o+o..o.o",
                "o.oooo.oooooo.oooo.o",
                "o+....+......+....+o",
                "oooooooooooooooooooo"
            },
            {
                "oooooooooooooooooooo",
                "o+...+........+...+o",
                "o.oooo+o+oo+o+oooo.o",
                "o.o..o.o.oo.o.o..o.o",
                "o.o..o.o.oo.o.o..o.o",
                "o.oooo+o+oo+o+oooo.o",
                "o+................+o",
                "o.oooo+o.oo.o+oooo.o",
                "o.oooo.o+oo+o.oooo.o",
                "o+................+o",
                "o.oooo+o+oo+o+oooo.o",
                "o.o..o.o.oo.o.o..o.o",
                "o.oooo+o+oo+o+oooo.o",
                "o+................+o",
                "o.oooo+o+oo+o+oooo.o",
                "o.o..o.o.oo.o.o..o.o",
                "o.o..o.o.oo.o.o..o.o",
                "o.oooo+o+oo+o+oooo.o",
                "o+...+........+...+o",
                "oooooooooooooooooooo"
            },
            {
                "oooooooooooooooooooo",
                "o+.....+......+...+o",
                "o.ooooo+oooo+ooooo.o",
                "o.+...+...+....+...o",
                "o.o.o.o+oooo.o.o.o+o",
                "o+o.o.o.oooo.o.o.o.o",
                "o.o.....oooo.....o+o",
                "o.ooooo.oooo.ooooo.o",
                "o......+...+......+o",
                "o+ooooo.ooo.oooooo.o",
                "o.+......+........+o",
                "o+o.ooo.oooo.ooo.o.o",
                "o.o.ooo.oooo.ooo.o.o",
                "o.+...+.......+...+o",
                "o.oooooooooooooooo+o",
                "o.+....+...+....+..o",
                "o+ooo.o+oooo+o.ooo+o",
                "o+ooo.o+oooo+o.ooo+o",
                "o+.....+......+....o",
                "oooooooooooooooooooo"
            }
        };

        std::list<std::pair<uint16_t, uint16_t>> _wall;
        std::list<std::pair<uint16_t, uint16_t>> _food;

    public:
        void init(const std::string &name) override;
        void stop() override;

        void event(IKey *key) override;
        void update() override;
        std::list<DrawObject *> draw() override;

        bool isWall(const std::pair<uint16_t, uint16_t> &pos);
        bool isSelf(const std::pair<int, int> &orient);

        void reset();

        [[nodiscard]] uint64_t getScore() const override;
    };
}


#endif //ARCADE_Nibbler_HPP
