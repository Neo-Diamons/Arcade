/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFML
*/

#include "Sfml.hpp"
#include <iostream>

extern "C"
{
    arc::IGraphical *create()
    {
        return new arc::SFML();
    }

    void destroy(const arc::IGraphical *ptr)
    {
        delete ptr;
    }
}

void arc::SFML::init(uint32_t width, uint32_t height)
{
    _width = width;
    _height = height;

    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(height, width), "SFML", sf::Style::Close | sf::Style::Titlebar);

    _font = std::make_shared<sf::Font>();

    if (!_font->loadFromFile("assets/JetBrainsMono-Regular.ttf"))
        throw std::runtime_error("Cannot load font /assets/JetBrainsMono-Regular.ttf");
}

void arc::SFML::stop()
{
    _font.reset();
    _preloadedTextures.clear();
    _window->close();
}

void arc::SFML::clear()
{
    _window->clear();
}

void arc::SFML::display() {
    _key.resetKey();
    while (_window->pollEvent(_event))
        switch (_event.type) {
            case sf::Event::Closed:
                _window->close();
                break;
            case sf::Event::KeyPressed:
                _key.setKeyPressed(_event.key.code);
                break;
            default: break;
        }
    for (auto &text : _texts)
        _window->draw(text);
    _texts.clear();
    _window->display();
}

bool arc::SFML::isOpen()
{
    return _window->isOpen();
}

void arc::SFML::drawText(int x, int y, const std::string &text, const Color &color)
{
    sf::Text sfText{text, *_font, 20};

    sfText.setPosition(static_cast<float>(x * 2), static_cast<float>(y * 2));
    sfText.setFillColor({static_cast<sf::Uint8>(color.r), static_cast<sf::Uint8>(color.g), static_cast<sf::Uint8>(color.b), 255});
    _texts.push_back(sfText);
}

void arc::SFML::drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color)
{
    sf::RectangleShape rectangle{{static_cast<float>(width), static_cast<float>(height)}};

    rectangle.setPosition(static_cast<float>(x), static_cast<float>(y));
    rectangle.setOutlineThickness(3);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor({static_cast<sf::Uint8>(color.r), static_cast<sf::Uint8>(color.g), static_cast<sf::Uint8>(color.b), 255});
    _window->draw(rectangle);
}

void arc::SFML::drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color& color)
{
    sf::RectangleShape rectangle{{static_cast<float>(width), static_cast<float>(height)}};

    rectangle.setPosition(static_cast<float>(x), static_cast<float>(y));
    rectangle.setFillColor({static_cast<sf::Uint8>(color.r), static_cast<sf::Uint8>(color.g), static_cast<sf::Uint8>(color.b), 255});
    _window->draw(rectangle);
}

void arc::SFML::drawTexture(int x, int y, uint32_t, uint32_t, const Texture &texture)
{
    if (!_preloadedTextures.contains(texture.GetPath())) {
        sf::Texture sfTexture;

        sfTexture.loadFromFile(texture.GetPath());
        _preloadedTextures.insert({texture.GetPath(), sfTexture});
    }

    const sf::Texture sfTexture = _preloadedTextures[texture.GetPath()];
    sf::Sprite sfSprite{sfTexture};

    sfSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    _window->draw(sfSprite);
}

arc::IKey *arc::SFML::getKey()
{
    return &_key;
}
