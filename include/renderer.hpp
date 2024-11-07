// Renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

class Renderer {
public:
    Renderer();
    ~Renderer();
    void initialize();
    void renderText(SDL_Renderer* renderer, TTF_Font* font,const std::vector<std::string>& lines, int cursorX, int cursorY);
    void clear();
    void present();
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
};

#endif // RENDERER_H
