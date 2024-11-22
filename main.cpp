#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

const int widthWindow = 512;
const int heightWindow = 512;
const int widthViewport = 1;
const int heightViewport = 1;
const float NearDistance = 1.0;

#include "matrix.cpp"
#include "render.cpp"



int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }

    SDL_CreateWindowAndRenderer(widthWindow, heightWindow, 0, &window, &renderer);
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    //SDL_RenderClear(renderer);
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    float offsetY = -2.0;
    Vec3 vAf(-2, -0.5+offsetY, 5); 
    Vec3 vBf(-2,  0.5+offsetY, 5);
    Vec3 vCf(-1,  0.5+offsetY, 5);
    Vec3 vDf(-1, -0.5+offsetY, 5);

    Vec3 vAb(-2, -0.5+offsetY, 6);
    Vec3 vBb(-2,  0.5+offsetY, 6);
    Vec3 vCb(-1,  0.5+offsetY, 6);
    Vec3 vDb(-1, -0.5+offsetY, 6);
    
    unsigned int time = SDL_GetTicks();

    while (1) {
        unsigned int now = SDL_GetTicks();
        unsigned int delta_time = now - time;
        if (SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT )
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
            if (event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();                   
                    break;
                }
            }
  
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        
        // The front face
        DrawLine(renderer, ProjectVertex(vAf), ProjectVertex(vBf));
        DrawLine(renderer, ProjectVertex(vBf), ProjectVertex(vCf));
        DrawLine(renderer, ProjectVertex(vCf), ProjectVertex(vDf));
        DrawLine(renderer, ProjectVertex(vDf), ProjectVertex(vAf));
        
        // The back face
        DrawLine(renderer, ProjectVertex(vAb), ProjectVertex(vBb));
        DrawLine(renderer, ProjectVertex(vBb), ProjectVertex(vCb));
        DrawLine(renderer, ProjectVertex(vCb), ProjectVertex(vDb));
        DrawLine(renderer, ProjectVertex(vDb), ProjectVertex(vAb));

        // The front-to-back edges
        DrawLine(renderer, ProjectVertex(vAf), ProjectVertex(vAb));
        DrawLine(renderer, ProjectVertex(vBf), ProjectVertex(vBb));
        DrawLine(renderer, ProjectVertex(vCf), ProjectVertex(vCb));
        DrawLine(renderer, ProjectVertex(vDf), ProjectVertex(vDb));

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        SDL_RenderPresent(renderer);
           



    }

    SDL_RenderPresent(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
