#ifndef DAMAGEABLE_H_
#define DAMAGEABLE_H_

#include <memory>
#include "units.h"

struct DamageText;

struct Damageable {
    virtual units::Game center_x() const = 0;
    virtual units::Game center_y() const = 0;
    virtual std::shared_ptr<DamageText> get_damage_text() = 0;

    virtual ~Damageable() = 0;
};

inline Damageable::~Damageable()
{
}

#endif // DAMAGEABLE_H_
