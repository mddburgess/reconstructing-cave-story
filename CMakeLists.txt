cmake_minimum_required(VERSION 3.8)
project(cavestory)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Boost REQUIRED COMPONENTS system)
find_package(SDL2 REQUIRED)

include_directories(cavestory ${Boost_INCLUDE_DIRS})
include_directories(cavestory ${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES
        src/animated_sprite.cc
        src/animated_sprite.h
        src/backdrop.cc
        src/backdrop.h
        src/config.cc
        src/config.h
        src/damage_text.cc
        src/damage_text.h
        src/first_cave_bat.cc
        src/first_cave_bat.h
        src/game.cc
        src/game.h
        src/graphics.cc
        src/graphics.h
        src/input.cc
        src/input.h
        src/main.cc
        src/map.cc
        src/map.h
        src/number_sprite.cc
        src/number_sprite.h
        src/player.cc
        src/player.h
        src/player_health.cc
        src/player_walking_animation.cc
        src/polar_star.cc
        src/polar_star.h
        src/projectile.h
        src/rectangle.h
        src/sprite.cc
        src/sprite.h
        src/sprite_state.h
        src/timer.cc
        src/timer.h
        src/units.h
        src/varying_width_sprite.h)

add_executable(cavestory ${SOURCE_FILES})
target_link_libraries(cavestory ${Boost_LIBRARIES})
target_link_libraries(cavestory ${SDL2_LIBRARIES})

add_custom_command(TARGET cavestory POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/content $<TARGET_FILE_DIR:cavestory>/content)