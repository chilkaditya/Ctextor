// Renderer.cpp
#include "renderer.hpp"
#include "check.hpp"
#include <iostream>

Renderer::Renderer() : window(nullptr), renderer(nullptr), font(nullptr) {}

Renderer::~Renderer() {
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Renderer::initialize() {
    scc(SDL_Init(SDL_INIT_VIDEO));
    scc(TTF_Init());
    window = scp(SDL_CreateWindow("Ctextor", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                800, 600, 
                                SDL_WINDOW_SHOWN));

    renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    font = tcp(TTF_OpenFont("fonts/SixtyfourConvergence-Regular.ttf", 10));
}

void Renderer::renderText(SDL_Renderer* renderer, TTF_Font* font,const std::vector<std::string>& lines, int cursorX, int cursorY) {
    // clear();
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    for (size_t i = 0; i < lines.size(); ++i) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, lines[i].c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Get the width and height of the texture
        int textWidth = textSurface->w;
        int textHeight = textSurface->h;

        // Define the position where the text will be rendered
        SDL_Rect renderQuad = { 10, 10 + static_cast<int>(i * textHeight), textWidth, textHeight };

        // Render the texture
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

        // Free resources
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        
    }
    int cursorHeight = TTF_FontHeight(font);
    int cursorXPos = 10; // Starting position for text rendering

    // Measure the width of the text up to cursorX
    std::string textBeforeCursor = lines[cursorY].substr(0, cursorX);
    TTF_SizeText(font, textBeforeCursor.c_str(), &cursorXPos, nullptr);
    cursorXPos += 10;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for cursor
    SDL_Rect cursorRect = {cursorXPos, 10 + cursorY * cursorHeight, 2, 15};
    SDL_RenderFillRect(renderer, &cursorRect);

    // present();
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}
