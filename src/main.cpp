#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "editor.hpp"
#include "renderer.hpp"

int main() {
    Renderer rend;
    rend.initialize();
    Editor editor;
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) quit = true;

            //Handling text input event
            else if (e.type == SDL_TEXTINPUT) editor.handleTextInput(e.text.text);

            else if (e.type == SDL_KEYDOWN) {

                //Handling backspace event
                if (e.key.keysym.sym == SDLK_BACKSPACE) editor.handleBackspace();

                //Handling enter event
                else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) editor.handleEnter();

                //Handling left-arrow key
                else if (e.key.keysym.sym == SDLK_LEFT) editor.handleLeftArrowKey();

                //Handling right-arrow key
                else if (e.key.keysym.sym == SDLK_RIGHT) editor.handleRightArrowKey();

                //Handling up-arrow key
                else if (e.key.keysym.sym == SDLK_UP) editor.handleUpArrowKey();

                //Handling down-arrow key
                else if (e.key.keysym.sym == SDLK_DOWN) editor.handleDownArrowKey();

            }
        }
        // Clear the screen
        SDL_SetRenderDrawColor(rend.renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(rend.renderer);

        rend.renderText(editor.getLines(), editor.cursor.getX(), editor.cursor.getY());

    }

    return 0;
}
