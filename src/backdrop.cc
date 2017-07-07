#include "backdrop.h"
#include <SDL2/SDL.h>
#include "game.h"

namespace {
    const units::Tile kBackgroundSize = 4;
}

Backdrop::~Backdrop()
{
}

FixedBackdrop::FixedBackdrop(const std::string& file_name, Graphics& graphics) {
    surface_id_ = graphics.loadImage(file_name);
}

void FixedBackdrop::draw(Graphics& graphics) const {
    for (units::Tile x = 0; x < Game::kScreenWidth; x += kBackgroundSize) {
        for (units::Tile y = 0; y < Game::kScreenHeight; y += kBackgroundSize) {
            SDL_Rect destination_rectangle;
            destination_rectangle.x = units::tileToPixel(x);
            destination_rectangle.y = units::tileToPixel(y);
            destination_rectangle.w = units::tileToPixel(kBackgroundSize);
            destination_rectangle.h = units::tileToPixel(kBackgroundSize);
            graphics.blitSurface(surface_id_, NULL, &destination_rectangle);
        }
    }
}
