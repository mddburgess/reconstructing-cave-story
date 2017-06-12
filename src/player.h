#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <map>
#include <array>
#include "sprite.h"
#include "rectangle.h"

struct Graphics;
struct Map;

struct Player {
    Player(Graphics& graphics, int x, int y);

    void update(int elapsed_time_ms, const Map& map);
    void draw(Graphics& graphics);

    void startMovingLeft();
    void startMovingRight();
    void stopMoving();

    void lookUp();
    void lookDown();
    void lookHorizontal();

    void startJump();
    void stopJump();

private:
    enum MotionType {
        STANDING,
        WALKING,
        JUMPING,
        FALLING
    };
    std::array<MotionType,4> motion_types = {STANDING, WALKING, JUMPING, FALLING};

    enum HorizontalFacing {
        LEFT,
        RIGHT
    };
    std::array<HorizontalFacing,2> horizontal_facings = {LEFT, RIGHT};

    enum VerticalFacing {
        UP,
        DOWN,
        HORIZONTAL
    };
    std::array<VerticalFacing,3> vertical_facings = {UP, DOWN, HORIZONTAL};

    struct SpriteState {
        SpriteState(MotionType motion_type = STANDING,
                    HorizontalFacing horizontal_facing = LEFT,
                    VerticalFacing vertical_facing = HORIZONTAL) :
            motion_type(motion_type),
            horizontal_facing(horizontal_facing),
            vertical_facing(vertical_facing) {}

        MotionType motion_type;
        HorizontalFacing horizontal_facing;
        VerticalFacing  vertical_facing;
    };
    friend bool operator<(const SpriteState& a, const SpriteState& b);

    struct Jump {
        Jump() : time_remaining_ms_(0), active_(false) {}

        void update(int elapsed_time_ms);
        void reset();
        void reactivate() { active_ = time_remaining_ms_ > 0; }
        void deactivate() { active_ = false; };
        bool active() const { return active_; }

    private:
        int time_remaining_ms_;
        bool active_;
    };

    void initializeSprites(Graphics& graphics);
    void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
    SpriteState getSpriteState();

    Rectangle leftCollision(int delta) const;
    Rectangle rightCollision(int delta) const;
    Rectangle topCollision(int delta) const;
    Rectangle bottomCollision(int delta) const;

    bool onGround() const { return on_ground_; }

    int x_, y_;
    float velocity_x_, velocity_y_;
    float acceleration_x_;
    HorizontalFacing horizontal_facing_;
    VerticalFacing  vertical_facing_;
    bool on_ground_;
    Jump jump_;
    std::map<SpriteState, std::shared_ptr<Sprite>> sprites_;
};

#endif // PLAYER_H_
