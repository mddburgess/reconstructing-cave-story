#include "head_bump_particle.h"

namespace {
    const units::Game kSourceX = 116;
    const units::Game kSourceY = 54;
    const units::Game kWidth = 6;
    const units::Game kHeight = 6;
    const units::MS kLifetime = 600;
}

HeadBumpParticle::HeadBumpParticle(Graphics& graphics,
                                   units::Game center_x,
                                   units::Game center_y)
: center_x_(center_x),
  center_y_(center_y),
  sprite_(graphics, "Caret",
          units::gameToPixel(kSourceX),
          units::gameToPixel(kSourceY),
          units::gameToPixel(kWidth),
          units::gameToPixel(kHeight)),
  timer_(kLifetime)
{
}

bool HeadBumpParticle::update(units::MS elapsed_time) {
    return !timer_.expired();
}

void HeadBumpParticle::draw(Graphics& graphics) {
    sprite_.draw(graphics, center_x_, center_y_);
}
