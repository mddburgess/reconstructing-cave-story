#include "flashing_pickup.h"

const std::string kSpriteName("NpcSym");
const units::Tile kDissipatingSourceX = 1;
const units::Tile kDissipatingSourceY = 0;
const units::Tile kHeartSourceX = 2;
const units::Tile kHeartSourceY = 5;
const Rectangle kHeartRectangle(5, 8, 21, 19);
const units::HP kHeartValue = 2;
const units::MS kLifetime = 8000;
const units::MS kStartPeriod = 400;
const units::MS kEndPeriod = 225;
const units::MS kFlickerPeriod = 75;
const units::MS kFlickerTime = kLifetime - 1000;
const units::MS kDissipateTime = kLifetime - 25;
const float kFlashInterpolation = (kEndPeriod * 1.0f - kStartPeriod * 1.0f) / kFlickerTime;

// static
std::shared_ptr<Pickup> FlashingPickup::heartPickup(Graphics& graphics,
                                                    units::Game center_x,
                                                    units::Game center_y)
{
    return std::shared_ptr<Pickup>(
            new FlashingPickup(graphics,
                               center_x,
                               center_y,
                               kHeartSourceX,
                               kHeartSourceY,
                               kHeartRectangle,
                               kHeartValue,
                               PickupType::HEALTH));
}

FlashingPickup::FlashingPickup(Graphics& graphics,
                               units::Game center_x,
                               units::Game center_y,
                               units::Tile source_x,
                               units::Tile source_y,
                               const Rectangle& rectangle,
                               const int value,
                               const Pickup::PickupType type) :
    x_(center_x - units::kHalfTile),
    y_(center_y - units::kHalfTile),
    timer_(kLifetime, true),
    flash_period_(kStartPeriod),
    sprite_(graphics,
            kSpriteName,
            units::tileToPixel(source_x),
            units::tileToPixel(source_y),
            units::tileToPixel(1),
            units::tileToPixel(1)),
    flash_sprite_(graphics,
                  kSpriteName,
                  units::tileToPixel(source_x + 1),
                  units::tileToPixel(source_y),
                  units::tileToPixel(1),
                  units::tileToPixel(1)),
    dissipating_sprite_(graphics,
                        kSpriteName,
                        units::tileToPixel(kDissipatingSourceX),
                        units::tileToPixel(kDissipatingSourceY),
                        units::tileToPixel(1),
                        units::tileToPixel(1)),
    rectangle_(rectangle),
    value_(value),
    type_(type)
{
}

Rectangle FlashingPickup::collisionRectangle() const
{
    return Rectangle(x_ + rectangle_.left(),
                     y_ + rectangle_.top(),
                     rectangle_.width(),
                     rectangle_.height());
}

bool FlashingPickup::update(units::MS, const Map&)
{
    flash_period_ = timer_.current_time() < kFlickerTime
            ? static_cast<units::MS>(kFlashInterpolation * timer_.current_time() + kStartPeriod)
            : kFlickerPeriod;

    return timer_.active();
}

void FlashingPickup::draw(Graphics& graphics)
{
    if (timer_.current_time() > kDissipateTime)
    {
        dissipating_sprite_.draw(graphics, x_, y_);
    }
    else if (timer_.current_time() > kFlickerTime)
    {
        if (timer_.current_time() / flash_period_ % 3 == 0)
        {
            sprite_.draw(graphics, x_, y_);
        }
        else if (timer_.current_time() / flash_period_ % 3 == 1)
        {
            flash_sprite_.draw(graphics, x_, y_);
        }
    }
    else
    {
        if (timer_.current_time() / flash_period_ % 2 == 0)
        {
            sprite_.draw(graphics, x_, y_);
        }
        else
        {
            flash_sprite_.draw(graphics, x_, y_);
        }
    }
}

