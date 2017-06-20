#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include <map>
#include <array>
#include "sprite.h"
#include "rectangle.h"
#include "units.h"
#include "number_sprite.h"

struct Graphics;
struct Map;

struct Player {
    Player(Graphics& graphics, units::Game x, units::Game y);

    void update(units::MS elapsed_time_ms, const Map& map);
    void draw(Graphics& graphics);
    void drawHUD(Graphics& graphics) const;

    void startMovingLeft();
    void startMovingRight();
    void stopMoving();

    void lookUp();
    void lookDown();
    void lookHorizontal();

    void startJump();
    void stopJump();

    void takeDamage();

    Rectangle damageRectangle() const;
    units::Game center_x() const { return x_ + units::kHalfTile; }

private:
    enum MotionType {
        STANDING,
        INTERACTING,
        WALKING,
        JUMPING,
        FALLING
    };
    std::array<MotionType,5> motion_types = {STANDING, INTERACTING, WALKING, JUMPING, FALLING};

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
    bool invincible_;
    units::MS invincible_time_;
    std::map<SpriteState, std::shared_ptr<Sprite>> sprites_;
    std::unique_ptr<Sprite> health_bar_sprite_;
    std::unique_ptr<Sprite> health_fill_sprite_;
    std::unique_ptr<NumberSprite> health_number_sprite_;
};

#endif // PLAYER_H_
