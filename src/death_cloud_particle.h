#ifndef DEATH_CLOUD_PARTICLE_
#define DEATH_CLOUD_PARTICLE_

#include "animated_sprite.h"
#include "particle.h"
#include "polar_vector.h"

struct Graphics;

struct DeathCloudParticle : Particle
{
    DeathCloudParticle(Graphics& graphics,
                       units::Game center_x,
                       units::Game center_y,
                       units::Velocity speed,
                       units::Degrees angle);

    bool update(units::MS elapsed_time) override;
    void draw(Graphics& graphics) override;

private:
    const units::Game center_x_, center_y_;
    const units::Velocity speed_;
    PolarVector offset_;
    AnimatedSprite sprite_;
};

#endif // DEATH_CLOUD_PARTICLE_
