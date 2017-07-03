#ifndef POWER_DORITO_PICKUP_H_
#define POWER_DORITO_PICKUP_H_

#include "animated_sprite.h"
#include "kinematics.h"
#include "pickup.h"

struct PowerDoritoPickup : Pickup
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

    Kinematics kinematics_x_, kinematics_y_;
    AnimatedSprite sprite_;
    SizeType size_;
};


#endif // POWER_DORITO_PICKUP_H_