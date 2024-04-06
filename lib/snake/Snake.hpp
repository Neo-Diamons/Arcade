/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#ifndef ARCADE_SNAKE_HPP
#define ARCADE_SNAKE_HPP

#include <list>

#include "include/IGame.hpp"
#include "include/Texture.hpp"

namespace arc {
    /**
     * @brief Snake game
     */
    class Snake final : public IGame {
        const uint16_t WIDTH = 20;
        const uint16_t HEIGHT = 20;

        std::string _name;

        std::list<std::pair<int, int>> _snake = {
            {-2 + WIDTH / 2, 0 + HEIGHT / 2},
            {-1 + WIDTH / 2, 0 + HEIGHT / 2},
            {0 + WIDTH / 2, 0 + HEIGHT / 2},
            {1 + WIDTH / 2, 0 + HEIGHT / 2},
        };

        std::pair<int, int> _orientation = {-1, 0};
        std::pair<int, int> _food = {std::rand() % WIDTH, std::rand() % HEIGHT};
        std::pair<int, int> _bonusFood = {-1, -1};

        enum STATE {
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

    public:
        void init(const std::string &name) override;
        void stop() override;

        void event(IKey *key) override;
        void update() override;
        std::list<DrawObject *> draw() override;

        [[nodiscard]] uint64_t getScore() const override;
    };
}


#endif //ARCADE_SNAKE_HPP
