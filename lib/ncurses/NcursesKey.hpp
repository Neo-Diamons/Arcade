/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Key
*/

#ifndef ARCADE_NCURSES_KEY_HPP
#define ARCADE_NCURSES_KEY_HPP

#include "include/IKey.hpp"

#include <ncurses.h>
#include <map>

namespace arc {
    /**
     * @brief Ncurses implementation of the key library
     */
    class NcursesKey final : public IKey {
    private:
        int _lastKeyPressed = UNKNOWN;
        const std::map<KeyEnum, int> _keyMap = {
                {A, 'a'},
                {B, 'b'},
                {C, 'c'},
                {D, 'd'},
                {E, 'e'},
                {F, 'f'},
                {G, 'g'},
                {H, 'h'},
                {I, 'i'},
                {J, 'j'},
                {K, 'k'},
                {L, 'l'},
                {M, 'm'},
                {N, 'n'},
                {O, 'o'},
                {P, 'p'},
                {Q, 'q'},
                {R, 'r'},
                {S, 's'},
                {T, 't'},
                {U, 'u'},
                {V, 'v'},
                {W, 'w'},
                {X, 'x'},
                {Y, 'y'},
                {Z, 'z'},
                {NUM0, '0'},
                {NUM1, '1'},
                {NUM2, '2'},
                {NUM3, '3'},
                {NUM4, '4'},
                {NUM5, '5'},
                {NUM6, '6'},
                {NUM7, '7'},
                {NUM8, '8'},
                {NUM9, '9'},
                {ESCAPE, 27},
                {SPACE, ' '},
                {RETURN, 36},
                {BACKSPACE, KEY_BACKSPACE},
                {UP, KEY_UP},
                {DOWN, KEY_DOWN},
                {LEFT, KEY_LEFT},
                {RIGHT, KEY_RIGHT}
        };

    public:
        bool isKeyPressed(KeyEnum key) override;
    };
}

#endif //ARCADE_NCURSES_KEY_HPP
