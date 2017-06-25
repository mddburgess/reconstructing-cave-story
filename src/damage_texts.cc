#include "damage_texts.h"

#include "damage_text.h"
#include "damageable.h"
#include "graphics.h"

void DamageTexts::addDamageable(std::shared_ptr<Damageable> damageable) {
    damage_text_map_[damageable->get_damage_text()] = std::weak_ptr<Damageable>(damageable);
}

void DamageTexts::update(units::MS elapsed_time) {
    for (DamageTextMap::value_type& kv : damage_text_map_) {
        kv.first->update(elapsed_time);
        if (auto damageable = kv.second.lock()) {
            kv.first->setPosition(damageable->center_x(), damageable->center_y());
        }
    }
}

void DamageTexts::draw(Graphics& graphics) {
    for (DamageTextMap::value_type& kv : damage_text_map_) {
        kv.first->draw(graphics);
    }
}
