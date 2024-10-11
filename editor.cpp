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
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::vector<TextLine>& lines, int cursorX,int cursorY) {
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    for (size_t i = 0; i < lines.size(); ++i) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, lines[i].content.c_str(), textColor);
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
    std::string textBeforeCursor = lines[cursorY].content.substr(0, cursorX);
    TTF_SizeText(font, textBeforeCursor.c_str(), &cursorXPos, nullptr);
    cursorXPos += 10; // Adjust for the left margin (starting position of text)
    // if (!lines[cursorY].content.empty() && cursorX > 0) {
    //     std::string textBeforeCursor = lines[cursorY].content.substr(0, cursorX);
    //     TTF_SizeText(font, textBeforeCursor.c_str(), &cursorXPos, nullptr);
    //     cursorXPos += 10; // Adjust for the left margin (starting position of text)
    // }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for cursor
    SDL_Rect cursorRect = {cursorXPos, 10 + cursorY * cursorHeight, 10, 20};
    SDL_RenderFillRect(renderer, &cursorRect);
    
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

    //Cursor position
    int cursorX = 0;
    int cursorY = 0;

    // Main loop
    bool quit = false;
    SDL_Event e;
    std::string currentText = lines[cursorY].content;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: {
                    quit = true;
                }
                case SDL_TEXTINPUT: {
                    currentText.insert(cursorX,e.text.text);
                    cursorX++;
                    lines[cursorY].content = currentText;
                    // std::cout << cursorX << std::endl;
                }
                case SDL_KEYDOWN: {
                    // Handle Backspace
                    if (e.key.keysym.sym == SDLK_BACKSPACE) {
                        if (cursorX > 0) {
                            currentText.erase(cursorX - 1, 1);  // Remove character before the cursor
                            cursorX--;  // Move cursor back
                            lines[cursorY].content = currentText;// Update current line
                        }
                        else if (cursorY > 0) {
                            // If at the start of a line, move to the end of the previous line
                            cursorY--;
                            cursorX = lines[cursorY].content.length();  // Move cursor to the end of the previous line
                            currentText = lines[cursorY].content;
                        }
                    }
                    // Handle Enter key
                    else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                        std::string newLineText = currentText.substr(cursorX);  // Text after the cursor becomes the new line
                        currentText = currentText.substr(0, cursorX);  // Text before the cursor stays in the current line
                        lines[cursorY].content = currentText;  // Update current line

                        lines.insert(lines.begin() + cursorY + 1, {newLineText});  // Insert new line
                        cursorY++;  // Move cursor to the new line
                        cursorX = 0;  // Reset cursor position to the start of the new line
                        currentText = lines[cursorY].content;  // Update current text to new line
                    }
                    
                }
            }
        }
        

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);

        // Render the text
        renderText(renderer, font, lines, cursorX,cursorY);

        

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
