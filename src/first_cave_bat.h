#ifndef FIRST_CAVE_BAT_H_
#define FIRST_CAVE_BAT_H_

#include "damageable.h"
#include "floating_number.h"
#include "rectangle.h"
#include "sprite_state.h"
#include "units.h"

struct Graphics;
struct Sprite;

struct FirstCaveBat : public Damageable
{
    FirstCaveBat(Graphics& graphics,
                 units::Game x,
                 units::Game y);

    virtual ~FirstCaveBat() override;

    bool update(units::MS elapsed_time,
                units::Game player_x);

    void draw(Graphics& graphics);

    Rectangle damageRectangle() const
    {
        return Rectangle(x_ + units::kHalfTile,
                         y_ + units::kHalfTile,
                         0,
                         0);
    }

    Rectangle collisionRectangle() const
    {
        return Rectangle(x_,
                         y_,
                         units::tileToGame(1),
                         units::tileToGame(1));
    }

    units::HP contactDamage() const;

    void takeDamage(units::HP damage)
    {
        damage_text_->addValue(damage);
        alive_ = false;
    }

    units::Game center_x() const override
    {
        return x_ + units::kHalfTile;
    }

    units::Game center_y() const override
    {
        return y_ + units::kHalfTile;
    }

    std::shared_ptr<FloatingNumber> get_damage_text() override
    {
        return damage_text_;
    }

private:

    typedef std::tuple<HorizontalFacing> SpriteTuple;
    struct SpriteState : public SpriteTuple
    {
        SpriteState(const SpriteTuple& tuple) :
            SpriteTuple(tuple)
        {
        }

        HorizontalFacing horizontal_facing() const
        {
            return std::get<0>(*this);
        }
    };

    void initializeSprites(Graphics& graphics);
    void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
    SpriteState getSpriteState() const;

    const units::Game flight_center_y_;
    bool alive_;
    units::Game x_, y_;
    units::Degrees flight_angle_;
    HorizontalFacing facing_;
    std::map<SpriteState, std::shared_ptr<Sprite>> sprites_;
    std::shared_ptr<FloatingNumber> damage_text_;
};

#endif // FIRST_CAVE_BAT_H_
