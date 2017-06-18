#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_

#include "sprite.h"
#include "units.h"

struct AnimatedSprite : public Sprite {
    AnimatedSprite(Graphics& graphics,
                   const std::string& file_path,
                   int source_x, int source_y,
                   int width, int height,
                   units::FPS fps, int num_frames);

    void update(units::MS elapsed_time_ms);

private:
    const units::MS frame_time_;
    const int num_frames_;
    int current_frame_;
    units::MS elapsed_time_;
};

#endif // ANIMATED_SPRITE_H_
