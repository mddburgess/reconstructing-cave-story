#ifndef GRAPHICS_H_
#define GRAPHICS_H_

struct SDL_Window;
struct SDL_Texture;
struct SDL_Rect;
struct SDL_Renderer;

struct Graphics {
    Graphics();
    ~Graphics();

    void blitSurface(SDL_Texture* source,
                     SDL_Rect* source_rectangle,
                     SDL_Rect* destination_rectangle);
    void clear();
    void flip();
    SDL_Renderer* getRenderer();

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
};

#endif // GRAPHICS_H_
