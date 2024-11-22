
Vec2 ViewportToCanvas(float x, float y){

    float xCanv = (x * widthWindow)/widthViewport;
    float yCanv = (y * heightWindow)/heightViewport;
    Vec2 pos(xCanv, yCanv); 
    return pos;
}
Vec2 ProjectVertex(Vec3 v){

    Vec2 pos = ViewportToCanvas(
            (v.get(0) * NearDistance) / -v.get(2), 
            (v.get(1) * NearDistance) / -v.get(2)); 
    return pos; 
}

void DrawLineLow(SDL_Renderer *renderer, Vec2 start, Vec2 end){
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
        //if (x > 0 && y > 0 && x < widthWindow && y < heightWindow){
        SDL_RenderDrawPoint(renderer, x, y); 
        //}       

        if (D > 0){
            y = y + yi;
            D = D + (2 * (dy - dx));
        }else{
            D = D + 2*dy;
        }

    }
    

}

void DrawLineHigh(SDL_Renderer *renderer, Vec2 start, Vec2 end){
    int dx = end.get(0) - start.get(0);
    int dy = end.get(1) - start.get(1);
    int xi = 1;

    if (dx < 0){
        xi = -1;
        dx = -dx;
    }

    int D = (2*dx)-dy;
    int x = start.get(0);
    /*
    std::cout << "x: " << x << std::endl;
    std::cout << "start x: " << (int)start.get(0) << std::endl;
    std::cout << "start y: " << (int)start.get(1) << std::endl;
    std::cout << "end x: " << (int)end.get(0) << std::endl;
    std::cout << "end y: " << (int)end.get(1) << std::endl;
    */
    for (int y = (int)start.get(1); y < (int)end.get(1); y++){
        //if (x > 0 && y > 0 && x < widthWindow && y < heightWindow){
        SDL_RenderDrawPoint(renderer, x, y); 
        //}
        if (D > 0){
            x = x + xi;
            D = D + (2 * (dx - dy));
        }else{
            D = D + 2*dx;
        }
        //std::cout << "y: " << y << std::endl;
        
    }
    
}

void DrawLine(SDL_Renderer *renderer, Vec2 start, Vec2 end){

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

}

