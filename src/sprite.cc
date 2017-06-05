#include "sprite.h"
#include "graphics.h"

Sprite::Sprite(const std::string& file_path,
               SDL_Renderer* renderer,
               int source_x, int source_y,
               int width, int height) {
    SDL_Surface* surface = SDL_LoadBMP(file_path.c_str());
    sprite_sheet_ = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    source_rect_.x = source_x;
    source_rect_.y = source_y;
    source_rect_.w = width;
    source_rect_.h = height;
}

Sprite::~Sprite() {
    SDL_DestroyTexture(sprite_sheet_);
}

void Sprite::draw(Graphics& graphics, int x, int y) {
    SDL_Rect destination_rectangle;
    destination_rectangle.x = x;
    destination_rectangle.y = y;
    destination_rectangle.w = source_rect_.w;
    destination_rectangle.h = source_rect_.h;

    graphics.blitSurface(sprite_sheet_, &source_rect_, &destination_rectangle);
}
