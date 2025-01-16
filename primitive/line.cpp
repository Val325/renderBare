void DrawLineLow(SDL_Renderer *renderer, Vec2<float> start, Vec2<float> end, double **z_buffer, triangleInfo triangl){
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
            if (x > 0 && x < 512 && y > 0 && y < 512){
                float z = start.get(0) + x*(start.get(0)-end.get(0));
                z = 1/z;
                //z = (2.0f * near) / (far + near - z * (far - near)); 
                //std::cout << "z: "<< z << std::endl;
                if (triangl.isUseTexture){
                    Vec2<float> point(x, y); 
                    Vec3<float> baricentric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3); 

                    float u = baricentric.get(0)*triangl.st1.get(0)+baricentric.get(1)*triangl.st2.get(0)+baricentric.get(2)*triangl.st3.get(0); 
                    float v = baricentric.get(0)*triangl.st1.get(1)+baricentric.get(1)*triangl.st2.get(1)+baricentric.get(2)*triangl.st3.get(1);

                    int widthTex = triangl.texture.width();
                    int heighTex = triangl.texture.height();
                    //std::cout << "u " << (int)abs(u*widthTex) << std::endl;
                    //std::cout << "v " << (int)abs(v*heighTex) << std::endl;
                    if (z < z_buffer[x][y]){

                        if ((int)abs(u*widthTex) < widthTex 
                                && (int)abs(v*heighTex) < heighTex
                                && !isnan(u) && !isnan(v)){
                            SDL_SetRenderDrawColor(renderer, (int)triangl.texture((int)abs(u*widthTex),(int)abs(v*heighTex),0,0),  (int)triangl.texture((int)abs(u*widthTex),(int)abs(v*heighTex),0,1),  (int)triangl.texture((int)abs(u*widthTex),(int)abs(v*heighTex),0,2), 255);
                            
                            z_buffer[x][y] = z;
                            SDL_RenderDrawPoint(renderer, x,y);
                        }
                        
                    }
                }else{
                    if (z < z_buffer[x][y]){
                        z_buffer[x][y] = z;
                        SDL_RenderDrawPoint(renderer, x, y);
                    }
                }
            }
    
        if (D > 0){
            y = y + yi;
            D = D + (2 * (dy - dx));
        }else{
            D = D + 2*dy;
        }

    }
}


void DrawLineHigh(SDL_Renderer *renderer, Vec2<float> start, Vec2<float> end, double **z_buffer,  triangleInfo triangl){
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
        if (x > 0 && x < 512 && y > 0 && y < 512){
            float z = start.get(1) + y*(start.get(1)-end.get(1));
            z = 1/z;
            if (triangl.isUseTexture){
                Vec2<float> point(x, y); 
                Vec3<float> baricentric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3); 
                float u = baricentric.get(0)*triangl.st1.get(0)+baricentric.get(1)*triangl.st2.get(0)+baricentric.get(2)*triangl.st3.get(0); 
                float v = baricentric.get(0)*triangl.st1.get(1)+baricentric.get(1)*triangl.st2.get(1)+baricentric.get(2)*triangl.st3.get(1);
                int widthTex = triangl.texture.width();
                int heighTex = triangl.texture.height();
                if (z < z_buffer[x][y]){
                    z_buffer[x][y] = z;
                    SDL_SetRenderDrawColor(renderer, (int)triangl.texture((int)u*widthTex,(int)v*heighTex,0,0), (int)triangl.texture((int)u*widthTex,(int)v*heighTex,0,1), (int)triangl.texture((int)u*widthTex,(int)v*heighTex,0,2), 255);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            } else{
                if (z < z_buffer[x][y]){
                    z_buffer[x][y] = z;
                    SDL_RenderDrawPoint(renderer, x, y);
                }
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



void DrawLine(SDL_Renderer *renderer, Vec2<float> start, Vec2<float> end, double **z_buffer,  triangleInfo triangl){

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


