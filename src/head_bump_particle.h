#ifndef HEAD_BUMP_PARTICLE_H_
#define HEAD_BUMP_PARTICLE_H_

#include "particle.h"
#include "polar_vector.h"
#include "sprite.h"
#include "timer.h"
#include "units.h"

struct Graphics;

struct HeadBumpParticle : public Particle {
    HeadBumpParticle(Graphics& graphics,
                     units::Game center_x,
                     units::Game center_y);

    bool update(units::MS elapsed_time) override;
    void draw(Graphics& graphics) override;

private:
    const units::Game center_x_, center_y_;
    Sprite sprite_;
    Timer timer_;
    PolarVector particle_a_, particle_b_;
    const units::Game max_offset_a_, max_offset_b_;
};

#endif // HEAD_BUMP_PARTICLE_H_
