#ifndef POLAR_STAR_H_
#define POLAR_STAR_H_

#include "sprite_state.h"
#include "units.h"

struct Graphics;
struct Sprite;

struct PolarStar {
    PolarStar(Graphics& graphics);

    void draw(Graphics& graphics,
              HorizontalFacing horizontal_facing,
              VerticalFacing vertical_facing,
              bool gun_up, units::Game x, units::Game y);

private:
    typedef std::tuple<HorizontalFacing, VerticalFacing> SpriteTuple;
    struct SpriteState : public SpriteTuple {
        SpriteState(const SpriteTuple& tuple) : SpriteTuple(tuple) {}
        HorizontalFacing horizontal_facing() const { return std::get<0>(*this); }
        VerticalFacing vertical_facing() const { return std::get<1>(*this); }
    };

    void initializeSprites(Graphics& graphics);
    void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);

    std::map<SpriteState, std::shared_ptr<Sprite>> sprite_map_;
};

#endif // POLAR_STAR_H_
