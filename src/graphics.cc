#include "graphics.h"
#include <SDL2/SDL.h>

namespace {
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;
}

Graphics::Graphics() {
    window_ = SDL_CreateWindow("Reconstructing Cave Story",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               kScreenWidth,
                               kScreenHeight,
                               SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

void Graphics::blitSurface(SDL_Texture* source,
                           SDL_Rect* source_rectangle,
                           SDL_Rect* destination_rectangle) {
    SDL_RenderCopy(renderer_, source, source_rectangle, destination_rectangle);
}

void Graphics::clear() {
    SDL_RenderClear(renderer_);
}

void Graphics::flip() {
    SDL_RenderPresent(renderer_);
}

SDL_Renderer* Graphics::getRenderer() {
    return renderer_;
}
