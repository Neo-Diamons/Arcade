/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "include/IGraphical.hpp"
#include "SDLKeys.hpp"

namespace arc {
    class SDL final : public IGraphical{
        private:
            uint32_t _width = 0;
            uint32_t _height = 0;

            SDL_Window *_window = nullptr;
            SDL_Renderer *_render = nullptr;
            bool _isOpen = false;

            std::shared_ptr<SDL_Event> _event = std::make_shared<SDL_Event>();
            SDLKeys _key{_event};

            TTF_Font *_font = nullptr;
            std::map<std::string, SDL_Texture *> _textures;

            uint64_t _fpsStartTime = 0;

        public:
            class SDLException final : public GraphicalException {
            public:
                explicit SDLException(const std::string &message) : GraphicalException("SDL", message) {}
            };

            void init(uint32_t width, uint32_t height) override;
            void stop() override;
            void clear() override;
            void display() override;

            void drawText(int x, int y, const std::string &text, const Color &color) override;
            void drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color) override;

            bool isOpen() override;

            void drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color &color) override;
            void drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture) override;

            IKey *getKey() override;
    };
}
