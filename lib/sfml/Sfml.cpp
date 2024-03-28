/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFML
*/

#include "Sfml.hpp"

extern "C"
{
    arc::IGraphical *create() {
        return new arc::SFML();
    }

    void destroy(const arc::IGraphical *ptr) {
        delete ptr;
    }
}

void arc::SFML::init(uint32_t width, uint32_t height) {
    this->_width = width;
    this->_height = height;
    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(height, width), "SFML");
    this->_font = std::make_shared<sf::Font>();
    if (!this->_font->loadFromFile("assets/JetBrainsMono-Regular.ttf"))
        throw std::runtime_error("Cannot load font /assets/JetBrainsMono-Regular.ttf");
}

void arc::SFML::stop() {
    this->_texts.clear();
    this->_sprites.clear();
    this->_rects.clear();
    this->_preloadedTextures.clear();
    this->_window->close();
}

void arc::SFML::clear() {
    this->_texts.clear();
    this->_sprites.clear();
    this->_rects.clear();
    this->_window->clear();
}

void arc::SFML::display() {
    while (this->_window->pollEvent(this->_event)){
        if (this->_event.type == sf::Event::Closed)
            this->_window->close();
        if (this->_event.type == sf::Event::KeyPressed)
            this->_key.setKeyPressed(this->_event.key.code);
    }
    this->_window->display();
}

bool arc::SFML::isOpen() {
    return this->_window->isOpen();
}

void arc::SFML::drawText(int x, int y, const std::string &text, const arc::Color &color) {
    std::shared_ptr<sf::Text> textPtr = std::make_shared<sf::Text>(text, *this->_font, 50);

    this->_texts.push_back(textPtr);
    textPtr->setPosition((float)x, (float)y);
    this->_window->draw(*textPtr);
}

void arc::SFML::drawRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color) {
    std::shared_ptr<sf::RectangleShape> rectPtr = std::make_shared<sf::RectangleShape>(sf::Vector2f((float)width, (float)height));

    this->_rects.push_back(rectPtr);
    rectPtr->setPosition((float)x, (float)y);
    rectPtr->setFillColor(sf::Color::Red);
    this->_window->draw(*rectPtr);
}

void arc::SFML::drawFillRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color) {
    std::shared_ptr<sf::RectangleShape> rectPtr = std::make_shared<sf::RectangleShape>(sf::Vector2f((float)width, (float)height));

    this->_rects.push_back(rectPtr);
    rectPtr->setPosition((float)x, (float)y);
    rectPtr->setFillColor(sf::Color::Red);
    this->_window->draw(*rectPtr);
}

void arc::SFML::drawTexture(int x, int y, uint32_t, uint32_t, const arc::Texture &texture) {
    sf::Texture *sfTexture;
    auto it = this->_preloadedTextures.find(texture.GetPath());

    if (it == this->_preloadedTextures.end()) {
        std::shared_ptr texturePtr = std::make_shared<sf::Texture>();

        this->_preloadedTextures.insert({texture.GetPath(), texturePtr});
        sfTexture = texturePtr.get();
        sfTexture->loadFromFile(texture.GetPath());
    } else {
        sfTexture = it->second.get();
    }

    sf::Sprite *sfSprite;
    std::shared_ptr spritePtr = std::make_shared<sf::Sprite>();

    sfSprite = spritePtr.get();
    sfSprite->setTexture(*sfTexture);
    sfSprite->setPosition((float)x, (float)y);
    this->_window->draw(*sfSprite);
}

arc::IKey *arc::SFML::getKey() {
    return &this->_key;
}
