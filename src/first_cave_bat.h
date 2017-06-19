#ifndef FIRST_CAVE_BAT_H_
#define FIRST_CAVE_BAT_H_

#include <memory>
#include "units.h"

struct Graphics;
struct Sprite;

struct FirstCaveBat {
    FirstCaveBat(Graphics& graphics, units::Game x, units::Game y);

    void update(units::MS elapsed_time);
    void draw(Graphics& graphics) const;

private:
    units::Game x_, y_;
    units::Degrees flight_angle_;
    std::shared_ptr<Sprite> sprite_;
};

#endif // FIRST_CAVE_BAT_H_
