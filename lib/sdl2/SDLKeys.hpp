/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Key
*/

#pragma once

#include "include/IKey.hpp"

#include <SDL2/SDL.h>
#include <memory>
#include <map>

namespace arc {
    /**
     * @brief SDL implementation of the key library
     */
    class SDLKeys final : public IKey {
    private:
        const std::map<KeyEnum, int> _keyMap = {
            {A, SDLK_a},
            {B, SDLK_b},
            {C, SDLK_c},
            {D, SDLK_d},
            {E, SDLK_e},
            {F, SDLK_f},
            {G, SDLK_g},
            {H, SDLK_h},
            {I, SDLK_i},
            {J, SDLK_j},
            {K, SDLK_k},
            {L, SDLK_l},
            {M, SDLK_m},
            {N, SDLK_n},
            {O, SDLK_o},
            {P, SDLK_p},
            {Q, SDLK_q},
            {R, SDLK_r},
            {S, SDLK_s},
            {T, SDLK_t},
            {U, SDLK_u},
            {V, SDLK_v},
            {W, SDLK_w},
            {X, SDLK_x},
            {Y, SDLK_y},
            {Z, SDLK_z},
            {NUM0, SDLK_0},
            {NUM1, SDLK_1},
            {NUM2, SDLK_2},
            {NUM3, SDLK_3},
            {NUM4, SDLK_4},
            {NUM5, SDLK_5},
            {NUM6, SDLK_6},
            {NUM7, SDLK_7},
            {NUM8, SDLK_8},
            {NUM9, SDLK_9},
            {ESCAPE, SDLK_ESCAPE},
            {SPACE, SDLK_SPACE},
            {RETURN, SDLK_RETURN},
            {BACKSPACE, SDLK_BACKSPACE},
            {UP, SDLK_UP},
            {DOWN, SDLK_DOWN},
            {LEFT, SDLK_LEFT},
            {RIGHT, SDLK_RIGHT}
        };

        std::shared_ptr<SDL_Event> _event{};

    public:
        SDLKeys() = delete;

        explicit SDLKeys(const std::shared_ptr<SDL_Event> &event)
            : _event(event)
        {}

        bool isKeyPressed(KeyEnum key) override;
    };
}
