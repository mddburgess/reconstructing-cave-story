#ifndef IMMOBILE_SINGLE_LOOP_PARTICLE_H_
#define IMMOBILE_SINGLE_LOOP_PARTICLE_H_

#include "animated_sprite.h"
#include "particle.h"

struct ImmobileSingleLoopParticle : public Particle
{
    ImmobileSingleLoopParticle(Graphics& graphics,
                                   const std::string file_name,
                                   units::Pixel source_x,
                                   units::Pixel source_y,
                                   units::Pixel source_width,
                                   units::Pixel source_height,
                                   units::FPS fps,
                                   units::Frame num_frames,
                                   units::Game x,
                                   units::Game y);

    bool update(units::MS elapsed_time) override;
    void draw(Graphics& graphics) override;

    virtual ~ImmobileSingleLoopParticle() {}

private:
    const units::Game x_, y_;
    AnimatedSprite sprite_;
};

#endif // IMMOBILE_SINGLE_LOOP_PARTICLE_H_
