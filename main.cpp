#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include <vector>

const int widthWindow = 512;
const int heightWindow = 512;
const int widthViewport = 1;
const int heightViewport = 1;
const float NearDistance = 0.5;

float angleOfView = 90; 
float near = 0.1; 
float far = 100;
#define PI 3.14159265

float degreeToRadian(float degrees){
    return degrees * (PI / 180);
}

#include "include/CImg.h"
#include "matrix.cpp"

struct triangleInfo{
    Vec3<float> vert1;
    Vec3<float> vert2;
    Vec3<float> vert3;

    Vec3<float> normal;

    Vec2<float> st1;
    Vec2<float> st2;
    Vec2<float> st3;
    cimg_library::CImg<unsigned char> texture;
    bool isUseTexture;
    
    Vec2<float> ScreenVert1;
    Vec2<float> ScreenVert2;
    Vec2<float> ScreenVert3;
};
#include "render.cpp"

int main(void) {
    SDL_Event event;
    SDL_Window *window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, widthWindow, heightWindow, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }

    SDL_CreateWindowAndRenderer(widthWindow, heightWindow, 0, &window, &renderer);
    

    Vec4<float> Vertex01(0, 0, 0, 1);
    Vec4<float> Vertex02(0, 0, 1, 1);
    Vec4<float> Vertex03(1, 0, 0, 1);
    
    Vec4<float> Vertex01tri1(0, 0, 0, 1);
    Vec4<float> Vertex02tri1(0, 0, 1, 1);
    Vec4<float> Vertex03tri1(1, 0, 0, 1);

    Vec4<float> Vertex01tri2(0, 0, 0, 1);
    Vec4<float> Vertex02tri2(0, 0, 1, 1);
    Vec4<float> Vertex03tri2(1, 0, 0, 1);
    //unsigned int time = SDL_GetTicks();

    Triangle trig(renderer, Vertex01, Vertex02, Vertex03);
    Triangle trig1(renderer, Vertex01tri1, Vertex02tri1, Vertex03tri1);
    Triangle trig2(renderer, Vertex01tri2, Vertex02tri2, Vertex03tri2);

    Vec2<float> topLeftPoint(0, 0);
    Vec2<float> topRightPoint(widthWindow, 0);
    Vec2<float> bottomLeftPoint(0, heightWindow);
    Vec2<float> bottomRightPoint(heightWindow, widthWindow);
        
    std::vector<std::vector<Vec2<float>>> cilpEdges;
    
    std::vector<Vec2<float>> topEdge;
    topEdge.push_back(topLeftPoint);
    topEdge.push_back(topRightPoint);
    
    std::vector<Vec2<float>> bottomEdge;
    bottomEdge.push_back(bottomLeftPoint);
    bottomEdge.push_back(bottomRightPoint);
    
    std::vector<Vec2<float>> rightEdge;
    rightEdge.push_back(topRightPoint);
    rightEdge.push_back(bottomRightPoint);
    
    std::vector<Vec2<float>> leftEdge;     
    leftEdge.push_back(topLeftPoint);
    leftEdge.push_back(bottomLeftPoint);
    
    cilpEdges.push_back(topEdge);
    cilpEdges.push_back(bottomEdge);
    cilpEdges.push_back(rightEdge);
    cilpEdges.push_back(leftEdge);

    float xPos = -2.0f;
    float yPos = -1.5f;
    float zPos = -1.0f;
    Vec3<float> cameraPos(xPos, yPos, zPos);

    unsigned int time = 0;
    while (1) {
        double **z_buffer = new double*[widthWindow];
        
        for(int i = 0; i < widthWindow; ++i) {
            z_buffer[i] = new double[heightWindow];
        }
        
        for (int i = 0; i < widthWindow; ++i){
            for (int j = 0; j < heightWindow; ++j){
                z_buffer[i][j] = std::numeric_limits<double>::infinity(); 
            }
        }

        unsigned int now = SDL_GetTicks();
        unsigned int delta_time = now - time;
        time = now;

        cameraPos.set(0, xPos);
        cameraPos.set(1, yPos);
        cameraPos.set(2, zPos);
        SDL_RenderClear(renderer);

        
        trig.Projection();
        trig.View(cameraPos);
        trig.Rotatition(90.0f, 0.0f, 90.0f);
        trig.Transform(1.0f, 0.0f, -1.0f);
        trig.Clip(cilpEdges);
        trig.Apply();
        trig.CullFace(cameraPos);
        trig.FixRender(cameraPos);
        trig.setTexture("src/tex4.jpg", true);
        trig.Unwrap(z_buffer);

        if (SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT )
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
            if (event.type == SDL_KEYDOWN){
                std::cout << "global coordinates x y z: " << xPos << " " << yPos << " " << zPos << std::endl; 
                float movement = 0.1;
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();                   
                        break;
                    case SDLK_w:
                        zPos += movement;                        
                        cameraPos.set(2, -zPos);
                        break;
                    case SDLK_s:
                        zPos -= movement;
                        cameraPos.set(2, -zPos);
                        break;
                    case SDLK_a:
                        xPos -= movement;
                        cameraPos.set(0, -xPos);
                        break;
                    case SDLK_d:
                        xPos += movement;
                        cameraPos.set(0, -xPos);
                        break;
                    case SDLK_LSHIFT:
                        yPos -= movement;
                        cameraPos.set(1, -yPos);
                        break;

                    case SDLK_LCTRL:
                        yPos += movement;
                        cameraPos.set(1, -yPos);
                        break;

                }
            }
  
        }

        for(int i = 0; i < widthWindow; ++i) {
            delete[] z_buffer[i];
        }
        delete[] z_buffer;

        /*for (int i = 0; i < 4; i++){
            triangles[i].Clip(cilpEdges);
            triangles[i].Projection(Projection, Camera, cameraPos);
            triangles[i].Unwrap();
            triangles[i].Render();
        }*/

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);


    }


    SDL_RenderPresent(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
