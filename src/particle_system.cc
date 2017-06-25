#include "particle_system.h"

#include "graphics.h"
#include "particle.h"
#include "units.h"

void ParticleSystem::update(units::MS elapsed_time) {
    for (auto iter = particles_.begin(); iter != particles_.end(); ) {
        if ((*iter)->update(elapsed_time)) {
            ++iter;
        } else {
            particles_.erase(iter++);
        }
    }
}

void ParticleSystem::draw(Graphics& graphics) {
    for (auto particle : particles_) {
        particle->draw(graphics);
    }
}
