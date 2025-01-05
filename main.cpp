#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <vector>
const int widthWindow = 512;
const int heightWindow = 512;
const int widthViewport = 1;
const int heightViewport = 1;
const float NearDistance = 0.5;

float angleOfView = 90; 
float near = 0.1; 
float far = 100;

#include "include/CImg.h"
#include "matrix.cpp"
#include "render.cpp"

#define PI 3.14159265

float degreeToRadian(float degrees){
    return degrees * (PI / 180);
}

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
    Vec3 vAf(-2, -2.5, 5); 
    Vec3 vBf(-2,  -1.5, 5);
    Vec3 vCf(-1,  -1.5, 5);
    Vec3 vDf(-1, -2.5, 5);

    Vec3 vAb(-2, -2.5, 6);
    Vec3 vBb(-2,  -1.5, 6);
    Vec3 vCb(-1,  -1.5, 6);
    Vec3 vDb(-1, -2.5, 6);
    
/*    Vec3 Vertex01(-2, -2.5, 3);
    Vec3 Vertex02(-2, -1.5, 4);
    Vec3 Vertex03(1, -1.5, 4);
*/

    Vec4 Vertex01(-2, -2.5, 3, 1);
    Vec4 Vertex02(-2, -1.5, 4, 1);
    Vec4 Vertex03(1, -1.5, 4, 1);
    //unsigned int time = SDL_GetTicks();

    // Texture coordinates
    Vec2 st1(0, 0);
    Vec2 st2(1, 0);
    Vec2 st3(0, 1);
    Triangle trig(renderer, Vertex01, Vertex02, Vertex03);

    Vec2 topLeftPoint(0, 0);
    Vec2 topRightPoint(widthWindow, 0);
    Vec2 bottomLeftPoint(0, heightWindow);
    Vec2 bottomRightPoint(heightWindow, widthWindow);
        
    std::vector<std::vector<Vec2>> cilpEdges; 
    
    std::vector<Vec2> topEdge;
    topEdge.push_back(topLeftPoint);
    topEdge.push_back(topRightPoint);
    
    std::vector<Vec2> bottomEdge;
    bottomEdge.push_back(bottomLeftPoint);
    bottomEdge.push_back(bottomRightPoint);
    
    std::vector<Vec2> rightEdge;
    rightEdge.push_back(topRightPoint);
    rightEdge.push_back(bottomRightPoint);
    
    std::vector<Vec2> leftEdge;     
    leftEdge.push_back(topLeftPoint);
    leftEdge.push_back(bottomLeftPoint);
    
    cilpEdges.push_back(topEdge);
    cilpEdges.push_back(bottomEdge);
    cilpEdges.push_back(rightEdge);
    cilpEdges.push_back(leftEdge);
   
    float xPoStart = 1.0f;
    float yPoStart = 0.0f;
    float zPoStart = -1.0f;

    float xPos = 1.0f;
    float yPos = 0.0f;
    float zPos = -1.0f;
    Vec3 cameraPos(xPos, yPos, zPos);

    //https://medium.com/@carmencincotti/lets-look-at-magic-lookat-matrices-c77e53ebdf78

    Mat4x4 Camera(
        1.0f, 0.0f, 0.0f, -xPos,
        0.0f, 1.0f, 0.0f, -yPos,
        0.0f, 0.0f, 1.0f, -zPos,
        0.0f, 0.0f, 0.0f, 1.0f 
    ); 
    float aspect_ratio = widthWindow / heightWindow;
    float scale = 1 / tan(angleOfView * 0.5 * PI / 180);
    float aspect_scale = 1 / (tan(angleOfView * 0.5 * PI / 180) * aspect_ratio);
    float depth_norm = -(far+near) / (far-near);
    float depth_norm2 = -2*far*near / (far-near);
    
    //https://medium.com/@jrespinozah/3d-graphics-the-perspective-projection-d2076f42cdf3
    Mat4x4 Projection(
        aspect_scale, 0, 0, 0,
        0, scale, 0, 0,
        0, 0, depth_norm, depth_norm2,
        0, 0, 1, 0 
    );
   /*  
    float top = scale * near;
    float bottom = -top;
    float right = top*aspect_ratio;
    float left = -top*aspect_ratio;
    
    float proj1 = 2*near / (right-left);
    float proj2 = 2*near / (top-bottom);
    float proj3 = -near*(right+left) / (right-left);
    float proj4 = -near*(top+bottom) / (top-bottom);
    float proj5 = -(far + near) / (far-near);
    float proj6 = 2*far*near / (near-far); 
    */
    //float proj1 = -far/ (far-near); 
    //float proj2 = -far*near / (far-near);
    //float proj1 = -(far + near / far-near); 
    //float proj2 = -(2*far*near / far-near);

//    Mat4x4 PV = Projection * Camera;
    //PV.show();
    //std::cout << "-------" << std::endl;
    //Vec4 pos1(1, 2, 3, 1);
    //pos1.show();
    //proj_pos1.show();

    //std::cout << "-------" << std::endl;
    //proj_pos1.show();
    //std::cout << "-------" << std::endl;
/*
        Vec4 proj_pos1 = PV.multiplyVec4(Vertex01);
        Vec3 pos1_NDC = proj_pos1.get_NDC();
        Vec2 pos1_Screen = pos1_NDC.get_screen_coords();

        Vec4 proj_pos2 = PV.multiplyVec4(Vertex02);
        Vec3 pos2_NDC = proj_pos2.get_NDC();
        Vec2 pos2_Screen = pos2_NDC.get_screen_coords();

        Vec4 proj_pos3 = PV.multiplyVec4(Vertex03);
        Vec3 pos3_NDC = proj_pos3.get_NDC();
        Vec2 pos3_Screen = pos3_NDC.get_screen_coords();
*/
    /*Projection.show();
    std::cout << "-------" << std::endl;
    Camera.show();
    std::cout << "-------" << std::endl;
    PV.show();
    std::cout << "-------" << std::endl;*/
    unsigned int time = 0;

    while (1) {
        unsigned int now = SDL_GetTicks();
        unsigned int delta_time = now - time;
        //bool canMove;
        time = now;
        /*if (delta_time > 1000){
            canMove = true;
            time = now;
        }else{
            canMove = false;            
        }
        std::cout << "now: " << now << std::endl; 
        std::cout << "delta_time: " << delta_time << std::endl; 
        */
        /*
        Mat4x4 PV = Projection * Camera;
        Vec4 proj_pos1 = PV.multiplyVec4(Vertex01);
        Vec3 pos1_NDC = proj_pos1.get_NDC();
        Vec2 pos1_Screen = pos1_NDC.get_screen_coords();

        Vec4 proj_pos2 = PV.multiplyVec4(Vertex02);
        Vec3 pos2_NDC = proj_pos2.get_NDC();
        Vec2 pos2_Screen = pos2_NDC.get_screen_coords();

        Vec4 proj_pos3 = PV.multiplyVec4(Vertex03);
        Vec3 pos3_NDC = proj_pos3.get_NDC();
        Vec2 pos3_Screen = pos3_NDC.get_screen_coords();
        */
        cameraPos.set(0, xPos);
        cameraPos.set(1, yPos);
        cameraPos.set(2, zPos);

        std::cout << "global coordinates x y z: " << xPos << " " << yPos << " " << zPos << std::endl; 
        if (SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT )
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
            if (event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();                   
                        break;
                    case SDLK_w:
                        zPos -= 0.1;
                        Camera.set(2, 3, zPos);
                        break;
                    case SDLK_s:
                        zPos += 0.1;
                        Camera.set(2, 3, zPos);
                        break;
                    case SDLK_a:
                        xPos += 0.1;
                        Camera.set(0, 3, xPos);
                        break;
                    case SDLK_d:
                        xPos -= 0.1;
                        Camera.set(0, 3, xPos);
                        break;
                    case SDLK_LSHIFT:
                        yPos += 0.1;
                        Camera.set(1, 3, yPos);
                        break;
                    case SDLK_LCTRL:
                        yPos -= 0.1;
                        Camera.set(1, 3, yPos);
                        break;

                }
            }
  
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        //trig.Unwrap();        

        // The front face
        /*DrawLine(renderer, ProjectVertex(vAf), ProjectVertex(vBf));
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
        DrawLine(renderer, ProjectVertex(vDf), ProjectVertex(vDb));*/
        
        //triangle
        //trig.Projection();
        trig.Clip(cilpEdges);
        trig.Projection(Projection, Camera, cameraPos);

        trig.Render();

        /*
        DrawLine(renderer, pos1_Screen, pos2_Screen);
        DrawLine(renderer, pos1_Screen, pos3_Screen);
        DrawLine(renderer, pos2_Screen, pos3_Screen);
        */

        /*
        DrawLine(renderer, ProjectVertex(Vertex01), ProjectVertex(Vertex02));
        DrawLine(renderer, ProjectVertex(Vertex01), ProjectVertex(Vertex03));
        DrawLine(renderer, ProjectVertex(Vertex02), ProjectVertex(Vertex03));
        */

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        SDL_RenderPresent(renderer);




    }

    SDL_RenderPresent(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
