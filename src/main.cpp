#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "editor.hpp"
#include "renderer.hpp"

int main() {
    std::cout << "reached" << std::endl;
    Renderer rend;
    std::cout << "reached" << std::endl;
    rend.initialize();
    std::cout << "reached" << std::endl;
    Editor editor;
    bool quit = false;
    SDL_Event e;
    // while(1);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            // std::cout << "reached" << std::endl;
            if (e.type == SDL_QUIT) quit = true;
            else if (e.type == SDL_TEXTINPUT) editor.handleTextInput(e.text.text);
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE) editor.handleBackspace();
                else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) editor.handleEnter();
            }
        }
        // Clear the screen
        SDL_SetRenderDrawColor(rend.renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(rend.renderer);

        rend.renderText(rend.renderer,rend.font,editor.getLines(), editor.cursor.getX(), editor.cursor.getY());
        // std::cout << "reached" << std::endl;

        // Update the screen
        SDL_RenderPresent(rend.renderer);
    }
    // Clean up
    TTF_CloseFont(rend.font);
    SDL_DestroyRenderer(rend.renderer);
    SDL_DestroyWindow(rend.window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
