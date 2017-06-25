#ifndef PROJECTILE_STAR_PARTICLE_H_
#define PROJECTILE_STAR_PARTICLE_H_

#include "animated_sprite.h"
#include "particle.h"

struct ProjectileStarParticle : public Particle
{
    ProjectileStarParticle(Graphics& graphics,
                           units::Game x,
                           units::Game y);

    bool update(units::MS elapsed_time) override;
    void draw(Graphics& graphics) override;

private:
    const units::Game x_, y_;
    AnimatedSprite sprite_;
};

#endif // PROJECTILE_STAR_PARTICLE_H_
