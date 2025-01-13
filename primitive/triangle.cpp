void fillBottomTriangle(SDL_Renderer *renderer, Vec2<float> v1, Vec2<float> v2, Vec2<float> v3, double **z_buffer,  triangleInfo triangl){
    float slope1 = (v2.get(0) - v1.get(0)) / (v2.get(1) - v1.get(1));

    float slope2 = (v3.get(0) - v1.get(0)) / (v3.get(1) - v1.get(1));
    

    float curx1 = v1.get(0);
    float curx2 = v1.get(0);

    for (int scanlineY = v1.get(1); scanlineY <= v2.get(1); scanlineY++)
    {
        //float z = (far*near)/(near+scanlineY*(far-near)); 
  
        Vec2<float> start((int)curx1, scanlineY);

        Vec2<float> end((int)curx2, scanlineY);
        DrawLine(renderer, start, end, z_buffer,  triangl);
 
        curx1 += slope1;
        curx2 += slope2;
    }
}

void fillTopTriangle(SDL_Renderer *renderer, Vec2<float> v1, Vec2<float> v2, Vec2<float> v3, double **z_buffer, triangleInfo triangl){
    //float slope1 = (v3.x - v1.x) / (v2.y - v1.y);
    //float slope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float slope1 = (v3.get(0) - v1.get(0)) / ((v3.get(1) - v1.get(1)));
    float slope2 = (v3.get(0) - v2.get(0)) / ((v3.get(1) - v2.get(1)));

    float curx1 = v3.get(0);
    float curx2 = v3.get(0);

    for (int scanlineY = v3.get(1); scanlineY > v1.get(1); scanlineY--)
    {

        //drawLine((int)curx1, scanlineY, (int)curx2, scanlineY);
        //float z = (far*near)/(near+scanlineY*(far-near));
        Vec2<float> start((int)curx1, scanlineY);
        
        Vec2<float> end((int)curx2, scanlineY);

        DrawLine(renderer, start, end, z_buffer, triangl);

        curx1 -= slope1;
        curx2 -= slope2;
    }
}

void DrawTriangle(SDL_Renderer *renderer, Vec2<float> v1, Vec2<float> v2, Vec2<float> v3, double **z_buffer,  triangleInfo triangl){
 
    if (v2.get(1) < v1.get(1)) { std::swap(v2, v1); }
    if (v3.get(1) < v1.get(1)) { std::swap(v3, v1); }
    if (v3.get(1) < v2.get(1)) { std::swap(v3, v2); }
    
    if (v2.get(1) == v3.get(1)){
        fillBottomTriangle(renderer, v1, v2, v3, z_buffer, triangl);
    }else if (v1.get(1) == v2.get(1)){
        fillTopTriangle(renderer, v1, v2, v3, z_buffer, triangl);
    }else{
        Vec2<float> verticle((int)(v1.get(0) + ((float)(v2.get(1) - v1.get(1)) / (float)(v3.get(1) - v1.get(1))) * (v3.get(0) - v1.get(0))), v2.get(1));
        fillBottomTriangle(renderer, v1, v2, verticle, z_buffer,  triangl);
        fillTopTriangle(renderer, v2, verticle, v3, z_buffer, triangl);
    }

}

/*void fillBottomTriangle_texture(SDL_Renderer *renderer, Vec2 v1, Vec2 v2, Vec2 v3){
    float slope1 = (v2.get(0) - v1.get(0)) / (v2.get(1) - v1.get(1));

    float slope2 = (v3.get(0) - v1.get(0)) / (v3.get(1) - v1.get(1));
    

    float curx1 = v1.get(0);
    float curx2 = v1.get(0);

    for (int scanlineY = v1.get(1); scanlineY <= v2.get(1); scanlineY++)
    {
        Vec2 start((int)curx1, scanlineY);

        Vec2 end((int)curx2, scanlineY);
        DrawLine(renderer, start, end);
 
        curx1 += slope1;
        curx2 += slope2;
    }
}

void fillTopTriangle_texture(SDL_Renderer *renderer, Vec2 v1, Vec2 v2, Vec2 v3){
    //float slope1 = (v3.x - v1.x) / (v2.y - v1.y);
    //float slope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float slope1 = (v3.get(0) - v1.get(0)) / ((v3.get(1) - v1.get(1)));
    float slope2 = (v3.get(0) - v2.get(0)) / ((v3.get(1) - v2.get(1)));

    float curx1 = v3.get(0);
    float curx2 = v3.get(0);

    for (int scanlineY = v3.get(1); scanlineY > v1.get(1); scanlineY--)
    {
        //drawLine((int)curx1, scanlineY, (int)curx2, scanlineY);

        Vec2 start((int)curx1, scanlineY);
        
        Vec2 end((int)curx2, scanlineY);

        DrawLine(renderer, start, end);

        curx1 -= slope1;
        curx2 -= slope2;
    }
}

void DrawTriangle_texture(SDL_Renderer *renderer, Vec2 v1, Vec2 v2, Vec2 v3, float **z_buffer){
    if (v2.get(1) < v1.get(1)) { std::swap(v2, v1); }
    if (v3.get(1) < v1.get(1)) { std::swap(v3, v1); }
    if (v3.get(1) < v2.get(1)) { std::swap(v3, v2); }
    
    if (v2.get(1) == v3.get(1)){
        fillBottomTriangle_texture(renderer, v1, v2, v3);
    }else if (v1.get(1) == v2.get(1)){
        fillTopTriangle_texture(renderer, v1, v2, v3);
    }else{
        Vec2 verticle((int)(v1.get(0) + ((float)(v2.get(1) - v1.get(1)) / (float)(v3.get(1) - v1.get(1))) * (v3.get(0) - v1.get(0))), v2.get(1));
        fillBottomTriangle_texture(renderer, v1, v2, verticle);
        fillTopTriangle_texture(renderer, v2, verticle, v3);
    }
}*/
