#ifndef DAMAGE_TEXTS_H_
#define DAMAGE_TEXTS_H_

#include <map>
#include <memory>
#include "units.h"

struct Damageable;
struct DamageText;
struct Graphics;

struct DamageTexts {
    void update(units::MS elapsed_time);
    void draw(Graphics& graphics);

private:
    typedef std::map<std::shared_ptr<DamageText>, std::weak_ptr<Damageable>> DamageTextMap;

    DamageTextMap damage_text_map_;
};

#endif // DAMAGE_TEXTS_H_
