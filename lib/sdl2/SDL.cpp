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
    _width = width;
    _height = height;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0)
        throw SDLException("SDL could not initialize.");
    _window = SDL_CreateWindow("Arcade", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
        throw SDLException("SDL window could not be created.");
    _render = SDL_CreateRenderer(this->_window, 0, SDL_RENDERER_ACCELERATED);
    if (_render == nullptr)
        throw SDLException("SDL renderer could not be created.");

    _isOpen = true;
    SDL_PollEvent(&(*_event));
}

bool arc::SDL::isOpen()
{
    return _isOpen;
}

void arc::SDL::stop()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_render);
    SDL_Quit();
    _isOpen = false;
}

void arc::SDL::clear()
{
    SDL_RenderClear(_render);
}

void arc::SDL::display()
{
    SDL_RenderPresent(_render);

    if (SDL_PollEvent(&(*_event)) && _event->type == SDL_QUIT)
        stop();
}

void arc::SDL::drawText(int x, int y, const std::string &text, const Color &color){}

void arc::SDL::drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.h = height;
    rect.w = width;
    SDL_SetRenderDrawColor(this->_render, color.r, color.g, color.b, 255);
    SDL_RenderDrawRect(this->_render, &rect);
}

void arc::SDL::drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color &color)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.h = height;
    rect.w = width;
    SDL_SetRenderDrawColor(this->_render, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(this->_render, &rect);
    SDL_RenderDrawRect(this->_render, &rect);
}

void arc::SDL::drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture)
{
    std::string path = texture.GetPath();
    SDL_Texture *text = IMG_LoadTexture(this->_render, path.c_str());
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.h = height;
    rect.w = width;
    SDL_SetRenderDrawColor(this->_render, 0, 0, 0, 0);
    SDL_RenderDrawRect(this->_render, &rect);
    SDL_RenderCopy(this->_render, text, NULL, &rect);
    SDL_DestroyTexture(text);
}

arc::IKey *arc::SDL::getKey()
{
    return &_key;
}
