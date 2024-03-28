/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/

#include <cstring>
#include <cmath>
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
    this->width = width;
    this->height = height;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0)
        throw SDLException("SDL could not initialize.");
    this->window = SDL_CreateWindow("Arcade", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        throw SDLException("SDL window could not be created.");
    SDL_UpdateWindowSurface(window);
}

void arc::SDL::stop()
{
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
void arc::SDL::clear(){}
void arc::SDL::display(){}
void arc::SDL::drawText(int x, int y, const std::string &text, const arc::Color &color){}
void arc::SDL::drawRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color){}
void arc::SDL::drawFillRect(int x, int y, uint32_t width, uint32_t height, const arc::Color &color){}
void arc::SDL::drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture){}
arc::IKey *arc::SDL::getKey()
{
    return &_key;
}
