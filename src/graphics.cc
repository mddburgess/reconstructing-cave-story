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
    for (SpriteMap::iterator iter = sprite_sheets_.begin();
         iter != sprite_sheets_.end();
         ++iter) {
        SDL_DestroyTexture(iter->second);
    }
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

Graphics::TextureID Graphics::loadImage(const std::string& file_path) {
    if (sprite_sheets_.count(file_path) == 0) {
        SDL_Surface* surface = SDL_LoadBMP(file_path.c_str());
        sprite_sheets_[file_path] = SDL_CreateTextureFromSurface(renderer_, surface);
        SDL_FreeSurface(surface);
    }
    return sprite_sheets_[file_path];
}

void Graphics::blitSurface(TextureID source,
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
