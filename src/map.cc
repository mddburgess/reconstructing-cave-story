#include "map.h"
#include "sprite.h"
#include "graphics.h"
#include "game.h"
#include "rectangle.h"

#include <memory>

// static
Map* Map::createTestMap(Graphics& graphics) {
    Map* map = new Map();

    map->backdrop_ = std::make_unique<FixedBackdrop>("content/bkBlue.bmp", graphics);
    const int num_rows = 15;
    const int num_cols = 20;
    map->tiles_ = std::vector<std::vector<Tile>>(
            num_rows, std::vector<Tile>(
                    num_cols, Tile()
            )
    );
    map->background_tiles_ = std::vector<std::vector<std::shared_ptr<Sprite>>>(
            num_rows, std::vector<std::shared_ptr<Sprite>>(
                    num_cols, std::shared_ptr<Sprite>()
            )
    );

    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(
            graphics, "content/PrtCave.bmp",
            Game::kTileSize, 0, Game::kTileSize, Game::kTileSize);
    Tile tile(WALL_TILE, sprite);
    const int row = 11;
    for (int col = 0; col < num_cols; ++col) {
        map->tiles_[row][col] = tile;
    }
    map->tiles_[10][5] = tile;
    map->tiles_[9][4] = tile;
    map->tiles_[8][3] = tile;
    map->tiles_[7][2] = tile;
    map->tiles_[10][3] = tile;

    std::shared_ptr<Sprite> chain_top = std::make_shared<Sprite>(
            graphics, "content/PrtCave.bmp",
            11 * Game::kTileSize, 2 * Game::kTileSize,
            Game::kTileSize, Game::kTileSize);
    std::shared_ptr<Sprite> chain_middle = std::make_shared<Sprite>(
            graphics, "content/PrtCave.bmp",
            12 * Game::kTileSize, 2 * Game::kTileSize,
            Game::kTileSize, Game::kTileSize);
    std::shared_ptr<Sprite> chain_bottom = std::make_shared<Sprite>(
            graphics, "content/PrtCave.bmp",
            13 * Game::kTileSize, 2 * Game::kTileSize,
            Game::kTileSize, Game::kTileSize);
    map->background_tiles_[8][2] = chain_top;
    map->background_tiles_[9][2] = chain_middle;
    map->background_tiles_[10][2] = chain_bottom;

    return map;
}

std::vector<Map::CollisionTile> Map::getCollidingTiles(const Rectangle& rectangle) const {
    const int first_row = rectangle.top() / Game::kTileSize;
    const int last_row = rectangle.bottom() / Game::kTileSize;
    const int first_col = rectangle.left() / Game::kTileSize;
    const int last_col = rectangle.right() / Game::kTileSize;
    std::vector<CollisionTile> collision_tiles;

    for (int row = first_row; row <= last_row; ++row) {
        for (int col = first_col; col <= last_col; ++col) {
            collision_tiles.push_back(CollisionTile(row, col, tiles_[row][col].tile_type));
        }
    }

    return collision_tiles;
}

void Map::update(units::MS elapsed_time_ms) {
    for (size_t row = 0; row < tiles_.size(); ++row) {
        for (size_t col = 0; col < tiles_[row].size(); ++col) {
            if (tiles_[row][col].sprite) {
                tiles_[row][col].sprite->update(elapsed_time_ms);
            }
        }
    }
}

void Map::drawBackground(Graphics& graphics) const {
    backdrop_->draw(graphics);
    for (size_t row = 0; row < background_tiles_.size(); ++row) {
        for (size_t col = 0; col < background_tiles_[row].size(); ++col) {
            if (background_tiles_[row][col]) {
                background_tiles_[row][col]->draw(
                        graphics, col * Game::kTileSize, row * Game::kTileSize);
            }
        }
    }
}

void Map::draw(Graphics& graphics) const {
    for (size_t row = 0; row < tiles_.size(); ++row) {
        for (size_t col = 0; col < tiles_[row].size(); ++col) {
            if (tiles_[row][col].sprite) {
                tiles_[row][col].sprite->draw(
                        graphics, col * Game::kTileSize, row * Game::kTileSize);
            }
        }
    }
}
