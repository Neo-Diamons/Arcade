/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SfmlKey
*/

#pragma once

#include <map>
#include <SFML/Window/Keyboard.hpp>
#include "include/IKey.hpp"

namespace arc {
    class SfmlKey final : public IKey {
    private:
        int _lastKeyPressed = UNKNOWN;
        const std::map<KeyEnum, sf::Keyboard::Key> _keyMap = {
                {A, sf::Keyboard::Key::A},
                {B, sf::Keyboard::Key::B},
                {C, sf::Keyboard::Key::C},
                {D, sf::Keyboard::Key::D},
                {E, sf::Keyboard::Key::E},
                {F, sf::Keyboard::Key::F},
                {G, sf::Keyboard::Key::G},
                {H, sf::Keyboard::Key::H},
                {I, sf::Keyboard::Key::I},
                {J, sf::Keyboard::Key::J},
                {K, sf::Keyboard::Key::K},
                {L, sf::Keyboard::Key::L},
                {M, sf::Keyboard::Key::M},
                {N, sf::Keyboard::Key::N},
                {O, sf::Keyboard::Key::O},
                {P, sf::Keyboard::Key::P},
                {Q, sf::Keyboard::Key::Q},
                {R, sf::Keyboard::Key::R},
                {S, sf::Keyboard::Key::S,},
                {T, sf::Keyboard::Key::T},
                {U, sf::Keyboard::Key::U},
                {V, sf::Keyboard::Key::V},
                {W, sf::Keyboard::Key::W},
                {X, sf::Keyboard::Key::X},
                {Y, sf::Keyboard::Key::Y},
                {Z, sf::Keyboard::Key::Z},
                {NUM0, sf::Keyboard::Key::Num0},
                {NUM1, sf::Keyboard::Key::Num1,},
                {NUM2, sf::Keyboard::Key::Num2},
                {NUM3, sf::Keyboard::Key::Num3},
                {NUM4, sf::Keyboard::Key::Num4},
                {NUM5, sf::Keyboard::Key::Num5},
                {NUM6, sf::Keyboard::Key::Num6},
                {NUM7, sf::Keyboard::Key::Num7},
                {NUM8, sf::Keyboard::Key::Num8},
                {NUM9, sf::Keyboard::Key::Num9},
                {ESCAPE, sf::Keyboard::Key::Escape},
                {SPACE, sf::Keyboard::Key::Space},
                {RETURN, sf::Keyboard::Key::Return},
                {BACKSPACE, sf::Keyboard::Key::BackSpace},
                {UP, sf::Keyboard::Key::Up},
                {DOWN, sf::Keyboard::Key::Down},
                {LEFT, sf::Keyboard::Key::Left},
                {RIGHT, sf::Keyboard::Key::Right}
        };

    public:
        bool isKeyPressed(KeyEnum key) override;
        void setKeyPressed(sf::Keyboard::Key key);
        void resetKey();
    };
}