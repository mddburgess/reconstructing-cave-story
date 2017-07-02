#ifndef PLAYER_H_
#define PLAYER_H_

#include "damage_text.h"
#include "damageable.h"
#include "gun_experience_hud.h"
#include "kinematics.h"
#include "number_sprite.h"
#include "polar_star.h"
#include "sprite.h"
#include "sprite_state.h"
#include "rectangle.h"
#include "timer.h"
#include "units.h"
#include "varying_width_sprite.h"

struct Graphics;
struct Map;
struct ParticleTools;
struct Projectile;

struct Player : public Damageable
{
    Player(Graphics& graphics, units::Game x, units::Game y);

    void update(units::MS elapsed_time_ms,
                const Map& map,
                ParticleTools& particle_tools);
    void draw(Graphics& graphics);
    void drawHUD(Graphics& graphics);

    void startMovingLeft();
    void startMovingRight();
    void stopMoving();

    void lookUp();
    void lookDown();
    void lookHorizontal();

    void startFire(ParticleTools& particle_tools);
    void stopFire();

    void startJump();
    void stopJump();

    void takeDamage(units::HP damage);

    Rectangle damageRectangle() const;

    units::Game center_x() const override
    {
        return kinematics_x_.position + units::kHalfTile;
    }

    units::Game center_y() const override
    {
        return kinematics_y_.position + units::kHalfTile;
    }

    std::shared_ptr<DamageText> get_damage_text() override
    {
        return damage_text_;
    }

    std::vector<std::shared_ptr<Projectile>> getProjectiles()
    {
        return polar_star_.getProjectiles();
    }

private:
    enum MotionType
    {
        FIRST_MOTION_TYPE,
        STANDING = FIRST_MOTION_TYPE,
        INTERACTING,
        WALKING,
        JUMPING,
        FALLING,
        LAST_MOTION_TYPE
    };
    enum StrideType
    {
        FIRST_STRIDE_TYPE,
        STRIDE_MIDDLE = FIRST_STRIDE_TYPE,
        STRIDE_LEFT,
        STRIDE_RIGHT,
        LAST_STRIDE_TYPE
    };

    typedef std::tuple<MotionType, HorizontalFacing, VerticalFacing, StrideType> SpriteTuple;

    struct SpriteState : public SpriteTuple
    {
        SpriteState(const SpriteTuple& tuple) :
            SpriteTuple(tuple)
        {
        }

        MotionType motion_type() const
        {
            return std::get<0>(*this);
        }

        HorizontalFacing horizontal_facing() const
        {
            return std::get<1>(*this);
        }

        VerticalFacing  vertical_facing() const
        {
            return std::get<2>(*this);
        }

        StrideType stride_type() const
        {
            return std::get<3>(*this);
        }
    };

    struct WalkingAnimation
    {
        WalkingAnimation();
        void update();
        void reset();
        StrideType stride() const;

    private:
        Timer frame_timer_;
        units::Frame current_frame_;
        bool forward_;
    };

    struct Health
    {
        Health(Graphics& graphics);
        void update(units::MS elapsed_time);
        void draw(Graphics& graphics);
        bool takeDamage(units::HP damage);

    private:
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
    void updateY(units::MS elapsed_time_ms,
                 const Map& map,
                 ParticleTools& particle_tools);

    MotionType motionType() const;

    bool onGround() const
    {
        return on_ground_;
    }

    bool gun_up() const
    {
        return motionType() == WALKING
               && walking_animation_.stride() != STRIDE_MIDDLE;
    }

    VerticalFacing vertical_facing() const
    {
        return onGround() && intended_vertical_facing_ == DOWN
            ? HORIZONTAL
            : intended_vertical_facing_;
    }

    bool spriteIsVisible() const;

    Kinematics kinematics_x_, kinematics_y_;
    int acceleration_x_;
    HorizontalFacing horizontal_facing_;
    VerticalFacing  intended_vertical_facing_;
    bool on_ground_;
    bool jump_active_;
    bool interacting_;
    Health health_;
    Timer invincible_timer_;
    std::shared_ptr<DamageText> damage_text_;
    WalkingAnimation walking_animation_;
    GunExperienceHUD gun_experience_hud_;
    PolarStar polar_star_;
    std::map<SpriteState, std::shared_ptr<Sprite>> sprites_;
};

#endif // PLAYER_H_
