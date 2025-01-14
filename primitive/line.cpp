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

    //std::cout << "z distance: " << z << std::endl;  
    for (int x = start.get(0); x < end.get(0); x++){

            //z = 1/z;
            //float z = ((1/ (1/start.get(1)))+x*((1/end.get(1))-(1/start.get(1))));
            //float z = (1/((1/start.get(1))+x*((1/end.get(1))-(1/start.get(1)))));        
            //float Mz = x/y;     
            //float startZ = start.get(0)/start.get(1);
            //float endZ = end.get(0)/end.get(1);
            //float z = 1/start.get(1) + (Mz-startZ) * ((1/end.get(1)-1/start.get(1))/(endZ-startZ));
            //z = 1/z;

            if (x > 0 && x < 512 && y > 0 && y < 512){
            //Vec2<double> point(x, y);
            //triangl.ScreenVert1.show(); 
            //Vec3<double> baric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3);
            //point.show();
            //float z = baric.get(0) * 1/triangl.vert1.get(2) + baric.get(1) * 1/triangl.vert2.get(2) + baric.get(2) * 1/triangl.vert3.get(2);            
            //float z = baric.get(0) * 1/triangl.ScreenVert1.get(1) + baric.get(1) * 1/triangl.ScreenVert2.get(1) + baric.get(2) * 1/triangl.ScreenVert3.get(1);
            //float d = 24;
            //float s = (pow(2, d) - 1);
            //z = s*(far/(far-near) + (1/z)*(-far*near/far-near));  
            //float z = -(triangl.d+triangl.normal.get(0)*x+triangl.normal.get(1)*y)/triangl.normal.get(2); 
            //float z = triangl.d;
            float z = start.get(0) + x*(start.get(0)-end.get(0));
            if (triangl.isUseTexture){
                Vec2<float> point(x, y); 
                Vec3<float> baricentric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3); 
                float u = baricentric.get(0)*triangl.st1.get(0)+baricentric.get(1)*triangl.st2.get(0)+baricentric.get(2)*triangl.st3.get(0); 
                float v = baricentric.get(0)*triangl.st1.get(1)+baricentric.get(1)*triangl.st2.get(1)+baricentric.get(2)*triangl.st3.get(1);
                //float u = baricentric.get(0)*0.1+baricentric.get(1)*0.7+baricentric.get(2)*0.1; 
                //float v = baricentric.get(0)*0.1+baricentric.get(1)*0.1+baricentric.get(2)*0.7;                

                int widthTex = triangl.texture.width();
                int heighTex = triangl.texture.height();
                //std::cout << "u " << (int)abs(u*widthTex) << std::endl;
                //std::cout << "v " << (int)abs(v*heighTex) << std::endl;
                
                
                if (z < z_buffer[x][y]){

                    z_buffer[x][y] = z;
                    //if ((int)u*x > 0 && (int)v*y > 0){
                        SDL_SetRenderDrawColor(renderer, (int)triangl.texture((int)abs(u*widthTex),(int)abs(v*heighTex),0,0),  (int)triangl.texture((int)abs(u*widthTex),(int)abs(v*heighTex),0,1),  (int)triangl.texture((int)abs(u*widthTex),(int)abs(v*heighTex),0,2), 255);
                    //}
                    SDL_RenderDrawPoint(renderer, x,y);
                }
            }else{
                if (z < z_buffer[x][y]){
                    //std::cout << "z " << z << std::endl;

                    z_buffer[x][y] = z;
                    SDL_RenderDrawPoint(renderer, x, y);
                }
                //std::cout << "z_buffer[x][y] " << z_buffer[x][y] << std::endl;
                //std::cout << "z_buffer: " << z_buffer[x][y] << std::endl; 
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

void DrawLineLow_texture(SDL_Renderer *renderer, Vec2<float> start, Vec2<float> end, float r, float g, float b){
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
    //std::cout << "z distance: " << z << std::endl;  

    for (int y = (int)start.get(1); y < (int)end.get(1); y++){
        //float z = ((1/ (1/triangl.vert1.get(2)))+x*((1/triangl.vert2.get(2))-(triangl.vert1.get(2))));
        //float z = (1/((1/start.get(1))+x*((1/end.get(1))-(1/start.get(1)))));        
        //Vec2 point(x, y);
        //Vec3 baric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3);
        //float z = baric.get(0) * 1/triangl.ScreenVert1.get(1) + baric.get(1) * 1/triangl.ScreenVert2.get(1) + baric.get(2) * 1/triangl.ScreenVert3.get(1);
        //z = 1/z;
        //float Mz = x/y;     
        //float startZ = start.get(0)/start.get(1);
        //float endZ = end.get(0)/end.get(1);
        //float z = 1/start.get(1) + (Mz-startZ) * ((1/end.get(1)-1/start.get(1))/(endZ-startZ));
    
        if (x > 0 && x < 512 && y > 0 && y < 512){

            //Vec2<double> point(x, y);
            //Vec3<double> baric = Barycentric(point, triangl.ScreenVert1, triangl.ScreenVert2, triangl.ScreenVert3);
            //float z = baric.get(0) * 1/triangl.vert1.get(2) + baric.get(1) * 1/triangl.vert2.get(2) + baric.get(2) * 1/triangl.vert3.get(2);
            //float z = baric.get(0) * 1/triangl.ScreenVert1.get(1) + baric.get(1) * 1/triangl.ScreenVert2.get(1) + baric.get(2) * 1/triangl.ScreenVert3.get(1);
            //float d = 24;
            //float s = (pow(2, d) - 1);
            //z = s*(far/(far-near) + (1/z)*(-far*near/far-near));  
            //std::cout << "z distance: " << z << std::endl; 
            //float z = -(triangl.d+triangl.normal.get(0)*x+triangl.normal.get(1)*y)/triangl.normal.get(2);             
            //float z = triangl.d;
            float z = start.get(1) + y*(start.get(1)-end.get(1));
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

void DrawLineHigh_texture(SDL_Renderer *renderer, Vec2<float> start, Vec2<float> end, float r, float g, float b){
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
