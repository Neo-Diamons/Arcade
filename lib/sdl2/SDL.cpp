/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL
*/

#include "SDL.hpp"

#include <SDL2/SDL_image.h>

#include "include/LibraryType.hpp"

extern "C" {
    arc::IGraphical *create()
    {
        return new arc::SDL();
    }

    void destroy(const arc::IGraphical *ptr)
    {
        delete ptr;
    }

    arc::LibraryType getType()
    {
        return arc::LibraryType::GRAPHICAL;
    }
}

void arc::SDL::init(uint32_t width, uint32_t height)
{
    _width = width;
    _height = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw SDLException("SDL could not initialize.");
    if (TTF_Init() < 0)
        throw SDLException("SDL_ttf could not initialize.");
    _window = SDL_CreateWindow("Arcade", 0, 0, static_cast<int>(width), static_cast<int>(height), SDL_WINDOW_SHOWN);
    if (_window == nullptr)
        throw SDLException("SDL window could not be created.");
    _render = SDL_CreateRenderer(_window, 0, SDL_RENDERER_ACCELERATED);
    if (_render == nullptr)
        throw SDLException("SDL renderer could not be created.");

    _font = TTF_OpenFont("assets/test.TTF", 12);
    SDL_PollEvent(&(*_event));
    _fpsStartTime = SDL_GetPerformanceCounter();

    _isOpen = true;
}

bool arc::SDL::isOpen()
{
    return _isOpen;
}

void arc::SDL::stop()
{
    for (auto &[fst, snd] : _textures) {
        SDL_DestroyTexture(snd);
        snd = nullptr;
    }
    TTF_CloseFont(_font);
    _font = nullptr;
    TTF_Quit();
    SDL_DestroyRenderer(_render);
    _render = nullptr;
    SDL_DestroyWindow(_window);
    _window = nullptr;
    SDL_Quit();
    _isOpen = false;
}

void arc::SDL::clear()
{
    drawFillRect(0, 0, _width, _height, {0, 0, 0});
    SDL_RenderClear(_render);
}

void arc::SDL::display()
{
    SDL_RenderPresent(_render);

    if (SDL_PollEvent(&(*_event)) && _event->type == SDL_QUIT)
        stop();

    const uint64_t fpsEndTime = SDL_GetPerformanceCounter();
    const uint64_t fps = (fpsEndTime - _fpsStartTime) * 1000 / SDL_GetPerformanceFrequency();
    SDL_Delay(1000 / 60 - fps);
    _fpsStartTime = SDL_GetPerformanceCounter();
}

void arc::SDL::drawText(int x, int y, const std::string &text, const Color &color)
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(_font, text.c_str(),
                                                       {
                                                           static_cast<Uint8>(color.r), static_cast<Uint8>(color.g),
                                                           static_cast<Uint8>(color.b), 255
                                                       });
    SDL_Texture *Message = SDL_CreateTextureFromSurface(_render, surfaceMessage);

    SDL_Rect rect = {x * 2, y * 2, 0, 0};
    SDL_QueryTexture(Message, nullptr, nullptr, &rect.w, &rect.h);
    SDL_RenderCopy(_render, Message, nullptr, &rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void arc::SDL::drawRect(int x, int y, uint32_t width, uint32_t height, const Color &color)
{
    const SDL_Rect rect{x, y, static_cast<int>(width), static_cast<int>(height)};
    SDL_SetRenderDrawColor(_render, color.r, color.g, color.b, 255);
    SDL_RenderDrawRect(_render, &rect);
}

void arc::SDL::drawFillRect(int x, int y, uint32_t width, uint32_t height, const Color &color)
{
    const SDL_Rect rect{x, y, static_cast<int>(width), static_cast<int>(height)};
    SDL_SetRenderDrawColor(_render, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(_render, &rect);
    SDL_RenderDrawRect(_render, &rect);
}

void arc::SDL::drawTexture(int x, int y, uint32_t width, uint32_t height, const Texture &texture)
{
    if (!_textures.contains(texture.GetPath()))
        _textures[texture.GetPath()] = IMG_LoadTexture(_render, texture.GetPath().c_str());

    SDL_Point point{x, y};
    SDL_QueryTexture(_textures[texture.GetPath()], nullptr, nullptr, &point.x, &point.y);

    const SDL_Rect srect{0, 0, static_cast<int>(width), static_cast<int>(height)};
    SDL_Rect drect{x, y, 0, 0};
    drect.w = static_cast<int>(width) < point.x ? static_cast<int>(width) : point.x;
    drect.h = static_cast<int>(height) < point.y ? static_cast<int>(height) : point.y;
    SDL_RenderCopy(_render, _textures[texture.GetPath()], &srect, &drect);
}

arc::IKey *arc::SDL::getKey()
{
    return &_key;
}
