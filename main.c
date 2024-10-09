#define SDL_MAIN_HANDLED
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

void scc(int code)
{
    if(code < 0){
        fprintf(stderr,"SDL ERROR: %s\n",SDL_GetError());
        exit(1);
    }
}
void *scp(void *ptr)
{
    if(ptr == NULL){
        fprintf(stderr,"SDL ERROR: %s\n",SDL_GetError());
        exit(1);
    }
    return ptr;
}

int main()
{
    scc(SDL_Init(SDL_INIT_VIDEO));
    SDL_Window* window = scp(SDL_CreateWindow(
        "Ctext",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,600,
        SDL_WINDOW_SHOWN
        /*SDL_WINDOW_RESIZEABLE*/)
    );
    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED));
    
    bool quit = false;
    while(!quit){
        SDL_Event event = {0};
        while(SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:{
                    quit = true;
                } break;
            }
        }
        scc(SDL_SetRenderDrawColor(renderer,0,0,0,0));
        scc(SDL_RenderClear(renderer));
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}