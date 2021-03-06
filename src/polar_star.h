#ifndef POLAR_STAR_H_
#define POLAR_STAR_H_

#include <array>
#include "projectile.h"
#include "rectangle.h"
#include "sprite_state.h"
#include "units.h"

struct GunExperienceHUD;
struct Graphics;
struct Map;
struct ParticleTools;
struct Sprite;

struct PolarStar {
    PolarStar(Graphics& graphics);

    void updateProjectiles(units::MS elapsed_time,
                           const Map& map,
                           ParticleTools& particle_tools);

    void drawHUD(Graphics& graphics, GunExperienceHUD& hud);

    void draw(Graphics& graphics,
              HorizontalFacing horizontal_facing,
              VerticalFacing vertical_facing,
              bool gun_up,
              units::Game player_x,
              units::Game player_y);

    void collectExperience(units::GunExperience experience);

    void damageExperience(units::GunExperience experience);

    void startFire(units::Game player_x,
                   units::Game player_y,
                   HorizontalFacing horizontal_facing,
                   VerticalFacing vertical_facing,
                   bool gun_up,
                   ParticleTools& particle_tools);

    void stopFire() {}

    std::vector<std::shared_ptr<::Projectile>> getProjectiles();

private:
    typedef std::tuple<HorizontalFacing, VerticalFacing> SpriteTuple;
    struct SpriteState : public SpriteTuple {
        SpriteState(const SpriteTuple& tuple) : SpriteTuple(tuple) {}
        HorizontalFacing horizontal_facing() const { return std::get<0>(*this); }
        VerticalFacing vertical_facing() const { return std::get<1>(*this); }
    };

    struct Projectile : public ::Projectile {
        Projectile(std::shared_ptr<Sprite> sprite,
                   HorizontalFacing horizontal_direction,
                   VerticalFacing vertical_direction,
                   units::Game x,
                   units::Game y,
                   units::GunLevel gun_level,
                   ParticleTools& particle_tools);


        bool update(units::MS elapsed_time,
                    const Map& map,
                    ParticleTools& particle_tools);

        void draw(Graphics& graphics);
        Rectangle collisionRectangle() const;
        units::HP contactDamage() const;
        void collideWithEnemy() { alive_ = false; }

    private:
        units::Game getX() const;
        units::Game getY() const;

        std::shared_ptr<Sprite> sprite_;
        const HorizontalFacing horizontal_direction_;
        const VerticalFacing vertical_direction_;
        const units::Game x_, y_;
        const units::GunLevel gun_level_;
        units::Game offset_;
        bool alive_;
    };

    units::Game gun_x(HorizontalFacing horizontal_facing, units::Game player_x) const {
        return horizontal_facing == LEFT
           ? player_x - units::kHalfTile
           : player_x;
    }
    units::Game gun_y(VerticalFacing vertical_facing, bool gun_up, units::Game player_y) const;

    void initializeSprites(Graphics& graphics);
    void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);

    units::GunLevel current_level() const;

    units::GunExperience current_experience_;
    std::map<SpriteState, std::shared_ptr<Sprite>> sprite_map_;
    std::array<std::shared_ptr<Sprite>, units::kMaxGunLevel> horizontal_projectiles_;
    std::array<std::shared_ptr<Sprite>, units::kMaxGunLevel> vertical_projectiles_;

    std::shared_ptr<Projectile> projectile_a_;
    std::shared_ptr<Projectile> projectile_b_;
};

#endif // POLAR_STAR_H_
