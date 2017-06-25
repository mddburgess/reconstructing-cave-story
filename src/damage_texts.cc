#include "damage_texts.h"

#include "damage_text.h"
#include "damageable.h"
#include "graphics.h"

void DamageTexts::addDamageable(std::shared_ptr<Damageable> damageable) {
    damage_text_map_[damageable->get_damage_text()] = std::weak_ptr<Damageable>(damageable);
}

void DamageTexts::update(units::MS elapsed_time) {
    for (auto iter = damage_text_map_.begin(); iter != damage_text_map_.end(); ) {
        iter->first->update(elapsed_time);
        if (auto damageable = iter->second.lock()) {
            iter->first->setPosition(damageable->center_x(), damageable->center_y());
        }
        if (iter->first->update(elapsed_time) || !iter->second.expired()) {
            ++iter;
        } else {
            damage_text_map_.erase(iter++);
        }
    }
}

void DamageTexts::draw(Graphics& graphics) {
    for (DamageTextMap::value_type& kv : damage_text_map_) {
        kv.first->draw(graphics);
    }
}
