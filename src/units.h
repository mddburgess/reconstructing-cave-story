#ifndef UNITS_H_
#define UNITS_H_

#include <cmath>

namespace units {

    typedef float Game;
    typedef int Pixel;
    typedef unsigned int Tile;
    typedef unsigned int Frame;

    typedef unsigned int MS;
    typedef unsigned int FPS;

    typedef float Velocity; // Game / MS
    typedef float Acceleration; // Game / MS^2

    namespace {
        const Game kTileSize = 32.0f;
    }

    inline Pixel gameToPixel(Game game) {
        return Pixel(round(game / 2));
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
}

#endif // UNITS_H_
