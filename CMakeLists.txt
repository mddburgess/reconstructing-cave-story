cmake_minimum_required(VERSION 3.8)
project(cavestory)

set(CMAKE_CXX_STANDARD 14)

set(CLANG_CXX_WARNINGS "-Weverything -Werror")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-c++98-compat")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-conditional-uninitialized")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-deprecated")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-double-promotion")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-exit-time-destructors")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-global-constructors")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-padded")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-shadow-field-in-constructor")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-shorten-64-to-32")
set(CLANG_CXX_WARNINGS "${CLANG_CXX_WARNINGS} -Wno-sign-conversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_WARNINGS}")

find_package(Boost REQUIRED COMPONENTS system)
find_package(SDL2 REQUIRED)

include_directories(cavestory ${Boost_INCLUDE_DIRS})
include_directories(cavestory ${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES
        src/accelerators.cc
        src/accelerators.h
        src/animated_sprite.cc
        src/animated_sprite.h
        src/backdrop.cc
        src/backdrop.h
        src/collision_rectangle.cc
        src/collision_rectangle.h
        src/collision_tile.cc
        src/collision_tile.h
        src/composite_collision_rectangle.cc
        src/composite_collision_rectangle.h
        src/config.cc
        src/config.h
        src/damage_texts.cc
        src/damage_texts.h
        src/damageable.cc
        src/damageable.h
        src/death_cloud_particle.cc
        src/death_cloud_particle.h
        src/first_cave_bat.cc
        src/first_cave_bat.h
        src/flashing_pickup.cc
        src/flashing_pickup.h
        src/floating_number.cc
        src/floating_number.h
        src/game.cc
        src/game.h
        src/graphics.cc
        src/graphics.h
        src/gun_experience_hud.cc
        src/gun_experience_hud.h
        src/head_bump_particle.cc
        src/head_bump_particle.h
        src/immobile_single_loop_particle.cc
        src/immobile_single_loop_particle.h
        src/input.cc
        src/input.h
        src/kinematics.h
        src/main.cc
        src/map.cc
        src/map.h
        src/map_collidable.cc
        src/map_collidable.h
        src/number_sprite.cc
        src/number_sprite.h
        src/particle.cc
        src/particle.h
        src/particle_system.cc
        src/particle_system.h
        src/pickup.cc
        src/pickup.h
        src/pickups.cc
        src/pickups.h
        src/player.cc
        src/player.h
        src/player_health.cc
        src/player_walking_animation.cc
        src/polar_star.cc
        src/polar_star.h
        src/polar_vector.h
        src/power_dorito_pickup.cc
        src/power_dorito_pickup.h
        src/projectile.cc
        src/projectile.h
        src/projectile_star_particle.cc
        src/projectile_star_particle.h
        src/projectile_wall_particle.cc
        src/projectile_wall_particle.h
        src/rectangle.h
        src/side_type.h
        src/simple_collision_rectangle.cc
        src/simple_collision_rectangle.h
        src/sprite.cc
        src/sprite.h
        src/sprite_state.h
        src/tile_type.h
        src/timer.cc
        src/timer.h
        src/units.h
        src/varying_width_sprite.cc
        src/varying_width_sprite.h
        src/vector2d.h)

add_executable(cavestory ${SOURCE_FILES})
target_link_libraries(cavestory ${Boost_LIBRARIES})
target_link_libraries(cavestory ${SDL2_LIBRARIES})

add_custom_command(TARGET cavestory POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/content $<TARGET_FILE_DIR:cavestory>/content)
