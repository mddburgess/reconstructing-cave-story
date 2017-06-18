#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <SDL2/SDL.h>
#include "units.h"

struct Graphics;

struct Sprite {
    Sprite(Graphics& graphics,
           const std::string& file_path,
           int source_x, int source_y,
           int width, int height);

    virtual void update(units::MS) {}
    void draw(Graphics& graphics, int x, int y);

protected:
    SDL_Rect source_rect_;

private:
    SDL_Texture* sprite_sheet_;
};

#endif // SPRITE_H_
