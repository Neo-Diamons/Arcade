/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFML
*/

#pragma once

#include "include/IGraphical.hpp"
#include "SfmlKey.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

namespace arc {
    class SFML final : public IGraphical {
    private:
        uint32_t _width = 0;
        uint32_t _height = 0;

        std::shared_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::Font> _font;

        sf::Event _event{};
        SfmlKey _key;

        std::map<std::string, sf::Texture> _preloadedTextures;
        std::list<sf::Text> _texts;

    public:
        class SFMLException final : public GraphicalException {
        public:
            explicit SFMLException(const std::string &message) : GraphicalException("SFML", message) {}
        };

        void init(uint32_t width, uint32_t height) override;
        void stop() override;
        void clear() override;
        void display() override;

        bool isOpen() override;

        void drawText(int x, int y, const std::string &text, const Color &color) override;
        void drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color) override;

        void drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color& color) override;
        void drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture) override;

        IKey *getKey() override;
    };
}
