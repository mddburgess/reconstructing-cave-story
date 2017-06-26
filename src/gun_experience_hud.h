#ifndef GUN_EXPERIENCE_HUD_H_
#define GUN_EXPERIENCE_HUD_H_

#include "sprite.h"
#include "timer.h"
#include "units.h"

struct GunExperienceHUD
{
    GunExperienceHUD(Graphics& graphics);

    void activateFlash() { flash_timer_.reset(); }
    void draw(Graphics& graphics, units::GunLevel gun_level);

private:
    Sprite experience_bar_sprite_, level_sprite_, flash_sprite_;
    Timer flash_timer_;
};

#endif //GUN_EXPERIENCE_HUD_H_
