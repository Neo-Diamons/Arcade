/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/

#pragma once

#include "include/Graphical.hpp"

namespace arc {
    class SDL : public arc::Graphical{
        public:
            class SDLException : public GraphicalException {
            public:
                explicit SDLException(const std::string &message) : GraphicalException("SDL", message) {}
            };

            void init() override;
            void stop() override;
            void clear() override;
            void display() override;

        private:
    };
}
