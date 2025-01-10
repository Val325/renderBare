void DrawLineLow(SDL_Renderer *renderer, Vec2 start, Vec2 end, float **z_buffer, triangleInfo triangl){
    int dx = end.get(0) - start.get(0);
    int dy = end.get(1) - start.get(1);
    int yi = 1;

    if (dy < 0){
        yi = -1;
        dy = -dy;
    }

    int D = (2*dy)-dx;
    int y = start.get(1);

    //std::cout << "z distance: " << z << std::endl;  
    for (int x = start.get(0); x < end.get(0); x++){

            //z = 1/z;
            //float z = ((1/ (1/start.get(1)))+x*((1/end.get(1))-(1/start.get(1))));
            //float z = (1/((1/start.get(1))+x*((1/end.get(1))-(1/start.get(1)))));        
            /*float Mz = x/y;     
            float startZ = start.get(0)/start.get(1);
            float endZ = end.get(0)/end.get(1);
            float z = 1/start.get(1) + (Mz-startZ) * ((1/end.get(1)-1/start.get(1))/(endZ-startZ));
            z = 1/z;*/

            if (x > 0 && x < 512 && y > 0 && y < 512){
            Vec2 point(x, y);
            Vec3 baric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3);
            baric.show();
            float z = baric.get(0) * 1/triangl.ScreenVert1.get(1) + baric.get(1) * 1/triangl.ScreenVert2.get(1) + baric.get(2) * 1/triangl.ScreenVert3.get(1);
                if (z < z_buffer[x][y]){

                    z_buffer[x][y] = z;
                    SDL_RenderDrawPoint(renderer, x, y);
                }
                //std::cout << "z_buffer[x][y] " << z_buffer[x][y] << std::endl;
                //std::cout << "z " << z << std::endl;
                //std::cout << "z_buffer: " << z_buffer[x][y] << std::endl; 
            }
    
        if (D > 0){
            y = y + yi;
            D = D + (2 * (dy - dx));
        }else{
            D = D + 2*dy;
        }

    }
}

void DrawLineLow_texture(SDL_Renderer *renderer, Vec2 start, Vec2 end, float r, float g, float b){
    int dx = end.get(0) - start.get(0);
    int dy = end.get(1) - start.get(1);
    int yi = 1;

    if (dy < 0){
        yi = -1;
        dy = -dy;
    }

    int D = (2*dy)-dx;
    int y = start.get(1);
  
    for (int x = start.get(0); x < end.get(0); x++){
        SDL_RenderDrawPoint(renderer, x, y); 

        if (D > 0){
            y = y + yi;
            D = D + (2 * (dy - dx));
        }else{
            D = D + 2*dy;
        }

    }
}

void DrawLineHigh(SDL_Renderer *renderer, Vec2 start, Vec2 end, float **z_buffer,  triangleInfo triangl){
    int dx = end.get(0) - start.get(0);
    int dy = end.get(1) - start.get(1);
    int xi = 1;

    if (dx < 0){
        xi = -1;
        dx = -dx;
    }

    int D = (2*dx)-dy;
    int x = start.get(0);
    //std::cout << "z distance: " << z << std::endl;  

    for (int y = (int)start.get(1); y < (int)end.get(1); y++){
        //float z = ((1/ (1/triangl.vert1.get(2)))+x*((1/triangl.vert2.get(2))-(triangl.vert1.get(2))));
        float z = (1/((1/start.get(1))+x*((1/end.get(1))-(1/start.get(1)))));        
        //Vec2 point(x, y);
        //Vec3 baric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3);
        //float z = baric.get(0) * 1/triangl.ScreenVert1.get(1) + baric.get(1) * 1/triangl.ScreenVert2.get(1) + baric.get(2) * 1/triangl.ScreenVert3.get(1);
        //z = 1/z;
            //float Mz = x/y;     
            //float startZ = start.get(0)/start.get(1);
            //float endZ = end.get(0)/end.get(1);
            //float z = 1/start.get(1) + (Mz-startZ) * ((1/end.get(1)-1/start.get(1))/(endZ-startZ));
    
        if (x > 0 && x < 512 && y > 0 && y < 512){
            Vec2 point(x, y);
            Vec3 baric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3);
            float z = baric.get(0) * 1/triangl.ScreenVert1.get(1) + baric.get(1) * 1/triangl.ScreenVert2.get(1) + baric.get(2) * 1/triangl.ScreenVert3.get(1);
            //std::cout << "z distance: " << z << std::endl; 
            if (z < z_buffer[x][y]){

                z_buffer[x][y] = z;
                SDL_RenderDrawPoint(renderer, x, y);
            }

        }
        if (D > 0){
            x = x + xi;
            D = D + (2 * (dx - dy));
        }else{
            D = D + 2*dx;
        }   
    } 
}

void DrawLineHigh_texture(SDL_Renderer *renderer, Vec2 start, Vec2 end, float r, float g, float b){
    int dx = end.get(0) - start.get(0);
    int dy = end.get(1) - start.get(1);
    int xi = 1;

    if (dx < 0){
        xi = -1;
        dx = -dx;
    }

    int D = (2*dx)-dy;
    int x = start.get(0);

    for (int y = (int)start.get(1); y < (int)end.get(1); y++){
        SDL_RenderDrawPoint(renderer, x, y); 
        if (D > 0){
            x = x + xi;
            D = D + (2 * (dx - dy));
        }else{
            D = D + 2*dx;
        }   
    } 
}

void DrawLine(SDL_Renderer *renderer, Vec2 start, Vec2 end, float **z_buffer,  triangleInfo triangl){

    if (abs(end.get(1) - start.get(1)) < abs(end.get(0) - start.get(0))){
        if (start.get(0) > end.get(0)){
            DrawLineLow(renderer, end, start, z_buffer, triangl);
        }else{
            DrawLineLow(renderer, start, end, z_buffer, triangl);
        }
    }else{
        if (start.get(1) > end.get(1)){
            DrawLineHigh(renderer, end, start, z_buffer, triangl);
        }else{
            DrawLineHigh(renderer, start, end, z_buffer, triangl);
        }
    }

}

/*void DrawLine_texture(SDL_Renderer *renderer, Vec2 start, Vec2 end){
    if (abs(end.get(1) - start.get(1)) < abs(end.get(0) - start.get(0))){
        if (start.get(0) > end.get(0)){
            DrawLineLow(renderer, end, start);
        }else{
            DrawLineLow(renderer, start, end);
        }
    }else{
        if (start.get(1) > end.get(1)){
            DrawLineHigh(renderer, end, start);
        }else{
            DrawLineHigh(renderer, start, end);
        }
    }

}*/
