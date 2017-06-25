#ifndef DAMAGE_TEXT_H_
#define DAMAGE_TEXT_H_

#include "timer.h"
#include "units.h"

struct Graphics;

struct DamageText {
    DamageText();
    void setDamage(units::HP damage);
    void update(units::MS elapsed_time);
    void setPosition(units::Game center_x, units::Game center_y);
    void draw(Graphics& graphics);

private:
    units::HP damage_;
    units::Game center_x_, center_y_;
    units::Game offset_y_;
    Timer timer_;
};

#endif // DAMAGE_TEXT_H_
