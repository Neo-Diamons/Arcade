/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/


#include <iostream>
#include "SDL.hpp"

extern "C"
{
    arc::IGraphical *create()
    {
        return new arc::SDL();
    }

    void destroy(const arc::IGraphical *ptr)
    {
        delete ptr;
    }
}

void arc::SDL::init(uint32_t width, uint32_t height)
{
    this->_width = width;
    this->_height = height;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0)
        throw SDLException("SDL could not initialize.");
    this->_window = SDL_CreateWindow("Arcade", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (this->_window == nullptr)
        throw SDLException("SDL window could not be created.");
    SDL_CreateRenderer(this->_window, 0, SDL_RENDERER_ACCELERATED);
    this->_isOpen = true;
    SDL_PollEvent(&(*_event));
}

bool arc::SDL::isOpen()
{
    return this->_isOpen;
}

void arc::SDL::stop()
{
    SDL_DestroyWindow(this->_window);
    SDL_Quit();
    this->_isOpen = false;
}

void arc::SDL::clear()
{
    if (SDL_PollEvent(&(*_event)) && (*_event).type == SDL_QUIT)
        stop();

    // SDL_Event event;

    // if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
    //     std::cout << "test" << std::endl;
    //     this->stop();
    // }
}

void arc::SDL::display(){}
void arc::SDL::drawText(int x, int y, const std::string &text, const arc::Color &color){}
void arc::SDL::drawRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color){}
void arc::SDL::drawFillRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color){}
void arc::SDL::drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture){}
arc::IKey *arc::SDL::getKey()
{
    return &_key;
}
