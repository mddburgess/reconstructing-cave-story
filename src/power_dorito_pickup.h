#ifndef POWER_DORITO_PICKUP_H_
#define POWER_DORITO_PICKUP_H_

#include "animated_sprite.h"
#include "kinematics.h"
#include "map_collidable.h"
#include "pickup.h"
#include "tile_type.h"

struct PowerDoritoPickup : public Pickup,
                           private MapCollidable
{
    enum SizeType
    {
        SMALL = 0,
        MEDIUM = 1,
        LARGE = 2
    };

    PowerDoritoPickup(Graphics& graphics,
                      units::Game center_x,
                      units::Game center_y,
                      SizeType size);

    Rectangle collisionRectangle() const override;
    bool update(units::MS elapsed_time, const Map& map) override;
    void draw(Graphics& graphics) override;
    int value() const override;

    PickupType type() const override
    {
        return EXPERIENCE;
    }

private:

    void onCollision(sides::SideType side,
                     bool is_delta_direction,
                     const tiles::TileType& tile_type) override;

    void onDelta(sides::SideType side) override
    {
    }

    Kinematics kinematics_x_, kinematics_y_;
    AnimatedSprite sprite_;
    SizeType size_;
    Timer timer_;
};


#endif // POWER_DORITO_PICKUP_H_
