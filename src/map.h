#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <memory>

struct Graphics;
struct Sprite;

struct Map {
    static Map* createTestMap(Graphics& graphics);

    void update(int elapsed_time_ms);
    void draw(Graphics& graphics) const;

private:
    std::vector<std::vector<std::shared_ptr<Sprite>>> foreground_sprites_;
};

#endif // MAP_H_
