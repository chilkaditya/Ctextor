#define SDL_MAIN_HANDLED   // Add this line
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Structure to store each line of text
struct TextLine {
    std::string content;
};

// Function to render text on the screen
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::vector<TextLine>& lines, int startY) {
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    for (size_t i = 0; i < lines.size(); ++i) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, lines[i].content.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Get the width and height of the texture
        int textWidth = textSurface->w;
        int textHeight = textSurface->h;

        // Define the position where the text will be rendered
        SDL_Rect renderQuad = { 10, startY + static_cast<int>(i * textHeight), textWidth, textHeight };

        // Render the texture
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

        // Free resources
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Text Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("fonts/SixtyfourConvergence-Regular.ttf", 10);  // Replace with the path to your TTF font file
    if (font == nullptr) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Vector to store the text lines
    std::vector<TextLine> lines;
    lines.push_back({" "});  // Start with an empty line

    // Main loop
    bool quit = false;
    SDL_Event e;
    std::string currentText = "";

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: {
                    quit = true;
                }
                case SDL_TEXTINPUT: {
                    currentText += e.text.text;
                    // std::cout << currentText << std::endl;
                    lines.back().content = currentText;  // Update the current line
                }
                case SDL_KEYDOWN: {
                    // Handle Backspace
                    if (e.key.keysym.sym == SDLK_BACKSPACE) {
                        if(!currentText.empty()){
                            currentText.pop_back();
                            std::cout << currentText << std::endl;
                            lines.back().content = currentText;
                        }
                        else if(lines.size() > 1){
                            lines.pop_back();
                            currentText = lines.back().content;
                        }
                        else currentText = " ";
                    }
                    // Handle Enter key
                    else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                        lines.push_back({" "});  // Add a new line
                        currentText = "";        // Reset current text
                    }
                }
            }
        }
        

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);

        // Render the text
        renderText(renderer, font, lines, 10);

        

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
