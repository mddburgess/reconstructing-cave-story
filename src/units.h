#ifndef UNITS_H_
#define UNITS_H_

#include <cmath>
#include "config.h"

namespace units {

    typedef int HP;

    typedef float Game;
    typedef int Pixel;
    typedef unsigned int Tile;
    typedef unsigned int Frame;
    typedef float Degrees;

    typedef unsigned int MS;
    typedef unsigned int FPS;

    typedef float Velocity; // Game / MS
    typedef float Acceleration; // Game / MS^2
    typedef float AngularVelocity; // Degrees / MS

    namespace {
        const Game kTileSize = 32.0f;
        const double kPi = atan(1) * 4;
    }

    inline Pixel gameToPixel(Game game) {
        return config::getGraphicsQuality() == config::HIGH_QUALITY
            ? Pixel(round(game))
            : Pixel(round(game) / 2);
    }

    inline Tile gameToTile(Game game) {
        return Tile(game / kTileSize);
    }

    inline Game tileToGame(Tile tile) {
        return tile * kTileSize;
    }

    inline Pixel tileToPixel(Tile tile) {
        return gameToPixel(tileToGame(tile));
    }

    inline double degreesToRadians(Degrees degrees) {
        return degrees * kPi / 180.0f;
    }

    inline Game sin(Degrees degrees) {
        return static_cast<Game>(std::sin(degreesToRadians(degrees)));
    }

    inline Game cos(Degrees degrees) {
        return static_cast<Game>(std::cos(degreesToRadians(degrees)));
    }

    const Game kHalfTile = tileToGame(1) / 2.0f;
}

#endif // UNITS_H_
