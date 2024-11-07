#pragma once
#include<iostream>

void scc(int code){
    if(code < 0){
        std::cerr << "SDL ERROR " << SDL_GetError() << std::endl;
        exit(1);
    }
}
template<typename T>
T *scp(T *ptr){
    if(ptr == NULL){
        std::cerr << "SDL ERROR " << SDL_GetError() << std::endl;
        exit(1);
    }
    return ptr;
}
template<typename T>
T *tcp(T *ptr){
    if(ptr == NULL){
        std::cerr << "TTF ERROR " << TTF_GetError() << std::endl;
        exit(1);
    }
    return ptr;
}