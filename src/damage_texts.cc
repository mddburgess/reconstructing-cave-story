#include "damage_texts.h"

#include "damage_text.h"
#include "graphics.h"

void DamageTexts::update(units::MS elapsed_time) {
    for (DamageTextMap::value_type& kv : damage_text_map_) {
        kv.first->update(elapsed_time);
    }
}

void DamageTexts::draw(Graphics& graphics) {
    for (DamageTextMap::value_type& kv : damage_text_map_) {
        kv.first->draw(graphics);
    }
}
