#ifndef VARYING_WIDTH_SPRITE_H_
#define VARYING_WIDTH_SPRITE_H_

#include <cassert>
#include "sprite.h"
#include "units.h"

struct Graphics;

struct VaryingWidthSprite : public Sprite
{
    VaryingWidthSprite(Graphics& graphics,
                       const std::string& file_name,
                       units::Pixel source_x,
                       units::Pixel source_y,
                       units::Pixel max_width,
                       units::Pixel initial_width,
                       units::Pixel height) :
        Sprite(graphics, file_name, source_x, source_y, initial_width, height),
        max_width_(max_width)
    {
    }

    virtual ~VaryingWidthSprite();

    void set_percentage_width(float percentage)
    {
        assert(percentage >= 0.0f && percentage <= 1.0f);
        source_rect_.w = static_cast<unsigned int>(percentage * max_width_);
    }

private:
    const units::Pixel max_width_;
};

#endif // VARYING_WIDTH_SPRITE_H_
