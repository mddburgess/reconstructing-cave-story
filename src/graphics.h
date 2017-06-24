#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

struct SDL_Window;
struct SDL_Texture;
struct SDL_Rect;
struct SDL_Renderer;

struct Graphics {
    typedef SDL_Texture* TextureID;

    Graphics();
    ~Graphics();

    TextureID loadImage(const std::string& file_name, bool black_is_transparent = false);

    void blitSurface(TextureID source,
                     SDL_Rect* source_rectangle,
                     SDL_Rect* destination_rectangle);
    void clear();
    void flip();

private:
    typedef std::map<std::string, SDL_Texture*> SpriteMap;
    SpriteMap sprite_sheets_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
};

#endif // GRAPHICS_H_
