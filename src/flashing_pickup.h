#ifndef FLASHING_PICKUP_H_
#define FLASHING_PICKUP_H_

#include <memory>
#include "pickup.h"
#include "sprite.h"
#include "timer.h"

struct FlashingPickup : public Pickup
{
    Rectangle collisionRectangle() const override;
    bool update(units::MS elapsed_time, const Map& map) override;
    void draw(Graphics& graphics) override;

    int value() const override
    {
        return value_;
    }

    PickupType type() const override
    {
        return type_;
    }

    static std::shared_ptr<Pickup> heartPickup(Graphics& graphics,
                                               units::Game center_x,
                                               units::Game center_y);

    static std::shared_ptr<Pickup> multiHeartPickup(Graphics& graphics,
                                                    units::Game center_x,
                                                    units::Game center_y);

private:

    FlashingPickup(Graphics& graphics,
                   units::Game center_x,
                   units::Game center_y,
                   units::Tile source_x,
                   units::Tile source_y,
                   const Rectangle& rectangle,
                   const int value,
                   const PickupType type);

    units::Game x_, y_;
    Timer timer_;
    units::MS flash_period_;
    Sprite sprite_, flash_sprite_, dissipating_sprite_;
    const Rectangle& rectangle_;
    const int value_;
    const PickupType type_;
};

#endif // FLASHING_PICKUP_H_
