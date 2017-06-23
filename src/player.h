#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <map>
#include "sprite.h"
#include "rectangle.h"
#include "units.h"
#include "number_sprite.h"
#include "varying_width_sprite.h"
#include "timer.h"
#include "damage_text.h"
#include "polar_star.h"
#include "sprite_state.h"

struct Graphics;
struct Map;

struct Player {
    Player(Graphics& graphics, units::Game x, units::Game y);

    void update(units::MS elapsed_time_ms, const Map& map);
    void draw(Graphics& graphics);
    void drawHUD(Graphics& graphics);

    void startMovingLeft();
    void startMovingRight();
    void stopMoving();

    void lookUp();
    void lookDown();
    void lookHorizontal();

    void startJump();
    void stopJump();

    void takeDamage(units::HP damage);

    Rectangle damageRectangle() const;
    units::Game center_x() const { return x_ + units::kHalfTile; }
    units::Game center_y() const { return y_ + units::kHalfTile; }

private:
    enum MotionType {
        FIRST_MOTION_TYPE,
        STANDING = FIRST_MOTION_TYPE,
        INTERACTING,
        WALKING,
        JUMPING,
        FALLING,
        LAST_MOTION_TYPE
    };

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

    struct Health {
        Health(Graphics& graphics);
        void update(units::MS elapsed_time);
        void draw(Graphics& graphics);
        bool takeDamage(units::HP damage);
    private:
        units::Game fillOffset(units::HP health) const;

        units::HP damage_;
        Timer damage_timer_;
        units::HP max_health_;
        units::HP current_health_;
        Sprite health_bar_sprite_;
        VaryingWidthSprite health_fill_sprite_;
        VaryingWidthSprite damage_fill_sprite_;
    };

    void initializeSprites(Graphics& graphics);
    void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
    SpriteState getSpriteState();

    Rectangle leftCollision(units::Game delta) const;
    Rectangle rightCollision(units::Game delta) const;
    Rectangle topCollision(units::Game delta) const;
    Rectangle bottomCollision(units::Game delta) const;

    void updateX(units::MS elapsed_time_ms, const Map& map);
    void updateY(units::MS elapsed_time_ms, const Map& map);

    bool onGround() const { return on_ground_; }

    bool spriteIsVisible() const;

    units::Game x_, y_;
    units::Velocity velocity_x_, velocity_y_;
    int acceleration_x_;
    HorizontalFacing horizontal_facing_;
    VerticalFacing  vertical_facing_;
    bool on_ground_;
    bool jump_active_;
    bool interacting_;
    Health health_;
    Timer invincible_timer_;
    DamageText damage_text_;
    PolarStar polar_star_;
    std::map<SpriteState, std::shared_ptr<Sprite>> sprites_;
};

#endif // PLAYER_H_
