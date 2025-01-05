#include <bits/stdc++.h>
/*class Triangle{
    public:
        Triangle(SDL_Renderer *rend, Vec3 Vert1, Vec3 Vert2, Vec3 Vert3);
        void Projection();
        void Clip(std::vector<std::vector<Vec2>> cilp);
        void Unwrap();
        void Render();
};*/
void SutherlandHodgman(SDL_Renderer *renderer,Vec2 point1, Vec2 point2, Vec2 point3, std::vector<std::vector<Vec2>> cilpEdge);
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

template <class Vec>
inline float edgeFunction(Vec a, Vec b, Vec c) {
    return (c.get(0) - a.get(0)) * (b.get(1) - a.get(1)) - (c.get(1) - a.get(1)) * (b.get(0) - a.get(0));
}

template <class Vec>
float Dot(Vec v1, Vec v2) {
    float result = 0;
    for (int i = 0; i < v1.sizeVec(); ++i) {
        result += v1.get(i) * v2.get(i);
    }
    return result;
}

template <class Vec>
Vec3 Barycentric(Vec p, Vec a, Vec b, Vec c)
{
    Vec v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = Dot(v0, v0);
    float d01 = Dot(v0, v1);
    float d11 = Dot(v1, v1);
    float d20 = Dot(v2, v0);
    float d21 = Dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;

    float res[3];
    // v = (d11 * d20 - d01 * d21) / denom
    res[0] = (d11 * d20 - d01 * d21) / denom;
    // w = (d00 * d21 - d01 * d20) / denom;
    res[1] = (d00 * d21 - d01 * d20) / denom;
    //u = 1.0f - v - w; 
    res[2] = 1.0f - res[0] - res[1];
    
    Vec3 vectorNew(res[0], res[1], res[2]);
    return vectorNew; 
}

bool isExistIntersection(Vec2 point1, Vec2 point2, int xSize, int ySize){
    bool xInClip;
    bool yInClip;
    if (point1.get(0) >= 0 && point1.get(0) < xSize){
        xInClip = true;
    }else{
        xInClip = false;
    }

    if (point2.get(0) >= 0 && point2.get(0) < ySize){
        yInClip = true;
    }else{
        yInClip = false;
    }

    return xInClip ^ yInClip; 
}
// Given three collinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(Vec2 p, Vec2 q, Vec2 r) 
{ 
    if (q.get(0) <= std::max(p.get(0), r.get(0)) && q.get(0) >= std::min(p.get(0), r.get(0)) && 
        q.get(1) <= std::max(p.get(1), r.get(1)) && q.get(1) >= std::min(p.get(1), r.get(1))) 
       return true; 
  
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are collinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Vec2 p, Vec2 q, Vec2 r) 
{ 
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
    // for details of below formula. 
    int val = (q.get(1) - p.get(1)) * (r.get(0) - q.get(0)) - 
              (q.get(0) - p.get(0)) * (r.get(1) - q.get(1)); 
  
    if (val == 0) return 0;  // collinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  


  
//https://www.cs.ucr.edu/~eldawy/19SCS133/notes/line-line-intersection.pdf
// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool isLineIntersect(Vec2 point1, Vec2 point2, Vec2 point3, Vec2 point4){
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(point1, point2, point3); 
    int o2 = orientation(point1, point2, point4); 
    int o3 = orientation(point3, point4, point1); 
    int o4 = orientation(point3, point4, point2); 
    
    // General case: lines intersect if they have different
    // orientations
    /*if (o1 != o2 && o3 != o4) {
      
        // Compute intersection point
        double a1 = point2.get(1) - point1.get(1);
        double b1 = point1.get(0) - point2.get(0);
        double c1 = a1 * point1.get(0) + b1 * point1.get(1);

        double a2 = point4.get(1) - point3.get(1);
        double b2 = point3.get(0) - point4.get(0);
        double c2 = a2 * point3.get(0) + b2 * point3.get(1);

        double determinant = a1 * b2 - a2 * b1;

        if (determinant != 0) {
            std::cout << "\n";
            std::cout << "x: " << (c1 * b2 - c2 * b1) / determinant << std::endl;
            std::cout << " y: " << (a1 * c2 - a2 * c1) / determinant << std::endl;
            std::cout << "\n";

        }
    } */
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(point1, point3, point2)) return true; 
  
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(point1, point4, point2)) return true; 
  
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(point3, point1, point4)) return true; 
  
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(point3, point2, point4)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
}

bool isPointInsideClip(Vec2 point, int Xsize, int Ysize){
    if (point.get(0) < Xsize 
        && point.get(0) > 0 
        && point.get(1) < Ysize
        && point.get(1) > 0){
        return true;
    }
    return false;
}

Vec2 isLineIntersectPos(Vec2 point1, Vec2 point2, Vec2 point3, Vec2 point4){
    Vec2 intersect;

    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(point1, point2, point3); 
    int o2 = orientation(point1, point2, point4); 
    int o3 = orientation(point3, point4, point1); 
    int o4 = orientation(point3, point4, point2); 
    
    // General case: lines intersect if they have different
    // orientations
    if (o1 != o2 && o3 != o4) {
      
        // Compute intersection point
        double a1 = point2.get(1) - point1.get(1);
        double b1 = point1.get(0) - point2.get(0);
        double c1 = a1 * point1.get(0) + b1 * point1.get(1);

        double a2 = point4.get(1) - point3.get(1);
        double b2 = point3.get(0) - point4.get(0);
        double c2 = a2 * point3.get(0) + b2 * point3.get(1);

        double determinant = a1 * b2 - a2 * b1;

        if (determinant != 0) {
            intersect.set(0, (c1 * b2 - c2 * b1) / determinant);
            intersect.set(1, (a1 * c2 - a2 * c1) / determinant);

            /*std::cout << "\n";
            std::cout << "x: " << (c1 * b2 - c2 * b1) / determinant << std::endl;
            std::cout << " y: " << (a1 * c2 - a2 * c1) / determinant << std::endl;
            std::cout << "\n";*/
        }
    } 
    return intersect; 
}



class Triangle{
    private:
        SDL_Renderer *renderer;
        bool isRender;
        Vec4 Vertex01Homogen;
        Vec4 Vertex02Homogen;
        Vec4 Vertex03Homogen;

        Vec3 Vertex01;
        Vec3 Vertex02;
        Vec3 Vertex03;

        Vec3 Coord01;
        Vec3 Coord02;
        Vec3 Coord03;

        Vec2 st2;
        Vec2 st1;
        Vec2 st0;

        Vec2 ScreenVertex01;
        Vec2 ScreenVertex02;
        Vec2 ScreenVertex03;
        cimg_library::CImg<unsigned char> texture;
    public:
        Triangle(SDL_Renderer *rend, Vec4 Vert1, Vec4 Vert2, Vec4 Vert3){
            renderer = rend;
            Vertex01Homogen = Vert1;
            Vertex02Homogen = Vert2;
            Vertex03Homogen = Vert3;
            isRender = true;
            Vec3 c2(1, 0, 0);
            Coord03 = c2;
            
            Vec3 c1(0, 1, 0);
            Coord02 = c1;

            Vec3 c0(0, 0, 1);
            Coord01 = c0;

            st2 = Vec2(0, 0);
            st1 = Vec2(1, 0);
            st0 = Vec2(0, 1);

        }
        Triangle(SDL_Renderer *rend, Vec3 Vert1, Vec3 Vert2, Vec3 Vert3){
            renderer = rend;
            Vertex01 = Vert1;
            Vertex02 = Vert2;
            Vertex03 = Vert3;

            Vec3 c2(1, 0, 0);
            Coord03 = c2;
            
            Vec3 c1(0, 1, 0);
            Coord02 = c1;

            Vec3 c0(0, 0, 1);
            Coord01 = c0;

            st2 = Vec2(0, 0);
            st1 = Vec2(1, 0);
            st0 = Vec2(0, 1);
            cimg_library::CImg<unsigned char> src("src/chess.png"); 
            texture = src;
            //std::cout << "height: " << texture.height() << std::endl; 
        }
        Triangle(SDL_Renderer *rend, Vec2 Vert1, Vec2 Vert2, Vec2 Vert3){
            renderer = rend;
            ScreenVertex01 = Vert1;
            ScreenVertex02 = Vert2;
            ScreenVertex03 = Vert3;

            Vec3 c2(1, 0, 0);
            Coord03 = c2;
            
            Vec3 c1(0, 1, 0);
            Coord02 = c1;

            Vec3 c0(0, 0, 1);
            Coord01 = c0;

            st2 = Vec2(0, 0);
            st1 = Vec2(1, 0);
            st0 = Vec2(0, 1);
            cimg_library::CImg<unsigned char> src("src/chess.png"); 
            texture = src;
            //std::cout << "height: " << texture.height() << std::endl; 
        }
        void Projection(Mat4x4 projetion, Mat4x4 camera, Vec3 startPos){
            //ScreenVertex01 = ProjectVertex(Vertex01);
            //ScreenVertex02 = ProjectVertex(Vertex02);
            //ScreenVertex03 = ProjectVertex(Vertex03);
            Mat4x4 PV = projetion * camera;
            Vec4 proj_pos1 = PV.multiplyVec4(Vertex01Homogen);
            Vec3 pos1_NDC = proj_pos1.get_NDC();
            ScreenVertex01 = pos1_NDC.get_screen_coords();
            std::cout << "z: " << startPos.get(2) << std::endl; 
            if (startPos.get(2) > -2.6){
                isRender = true;
            }else{
                isRender = false;        
            }

            const int overflow = 10000;
            bool vert1render = true;
            bool vert2render = true;
            bool vert3render = true;
            if (ScreenVertex01.get(0) > overflow){
                ScreenVertex01.set(0, overflow);
            }
            if (ScreenVertex01.get(1) > overflow){
                ScreenVertex01.set(1, overflow);
            }
            if (ScreenVertex01.get(0) < -overflow){
                ScreenVertex01.set(0, -overflow);
            }
            if (ScreenVertex01.get(1) < -overflow){
                ScreenVertex01.set(1, -overflow);
            }


            /*if (!(ScreenVertex01.get(0) < 512
                && ScreenVertex01.get(0) > 0
                && ScreenVertex01.get(1) < 512
                && ScreenVertex01.get(1) > 0)){
                vert1render = false;
            }else{
                vert1render = true;
            }*/

            //ScreenVertex01.show();

            Vec4 proj_pos2 = PV.multiplyVec4(Vertex02Homogen);
            Vec3 pos2_NDC = proj_pos2.get_NDC();
            ScreenVertex02 = pos2_NDC.get_screen_coords();

            if (ScreenVertex02.get(0) > overflow){
                ScreenVertex02.set(0, overflow);
            }
            if (ScreenVertex02.get(1) > overflow){
                ScreenVertex02.set(1, overflow);
            }
            if (ScreenVertex02.get(0) < -overflow){
                ScreenVertex02.set(0, -overflow);
            }
            if (ScreenVertex02.get(1) < -overflow){
                ScreenVertex02.set(1, -overflow);
            }

           /* if (!(ScreenVertex02.get(0) < 512
                && ScreenVertex02.get(0) > 0
                && ScreenVertex02.get(1) < 512
                && ScreenVertex02.get(1) > 0)){
                vert2render = false;
            }else{
                vert2render = true;
            }*/
            //ScreenVertex02.show();

            Vec4 proj_pos3 = PV.multiplyVec4(Vertex03Homogen);
            Vec3 pos3_NDC = proj_pos3.get_NDC();
            ScreenVertex03 = pos3_NDC.get_screen_coords();
            if (ScreenVertex03.get(0) > overflow){
                ScreenVertex03.set(0, overflow);
            }
            if (ScreenVertex03.get(1) > overflow){
                ScreenVertex03.set(1, overflow);
            }
            if (ScreenVertex03.get(0) < -overflow){
                ScreenVertex03.set(0, -overflow);
            }
            if (ScreenVertex03.get(1) < -overflow){
                ScreenVertex03.set(1, -overflow);
            }

           /* if (!(ScreenVertex03.get(0) < 512
                && ScreenVertex03.get(0) > 0
                && ScreenVertex03.get(1) < 512
                && ScreenVertex03.get(1) > 0)){
                vert3render = false;
            }else{
                vert3render = true;
            }*/
            //isRender = vert1render || vert2render || vert3render; 
            //ScreenVertex03.show();

        }
        void Clip(std::vector<std::vector<Vec2>> cilp){
            if (isRender){
                SutherlandHodgman(renderer, ScreenVertex01, ScreenVertex02, ScreenVertex03, cilp);
            }
        }
        void Unwrap(){

        }
        void Render(){
            if (isRender){
                DrawLine(renderer, ScreenVertex01, ScreenVertex02);
                DrawLine(renderer, ScreenVertex01, ScreenVertex03);
                DrawLine(renderer, ScreenVertex02, ScreenVertex03);
            }
        }

};

void SutherlandHodgman(SDL_Renderer *renderer,Vec2 point1, Vec2 point2, Vec2 point3, std::vector<std::vector<Vec2>> cilpEdge){
    std::vector<Vec2> output;
    output.push_back(point1);
    output.push_back(point2);
    output.push_back(point3);

    std::vector<Vec2> returntriangle;

    for (int i = 0; i < cilpEdge.size(); i++){


        for (int j = 0; j < output.size(); j++){
            Vec2 current_point = output[j];
            //Vec2 perv_point = output[(j-1)%output.size()];
            Vec2 perv_point;
            if ((j-1) < 0){
                perv_point = output[output.size()-1];
            }else{
                perv_point = output[j-1];
            }

            if (isLineIntersect(perv_point, current_point,cilpEdge[i][0], cilpEdge[i][1])) {
                Vec2 Intersecting_point = isLineIntersectPos(perv_point, current_point, cilpEdge[i][0], cilpEdge[i][1]);
                //std::cout << "if (isLineIntersect(perv_point, current_point,cilpEdge[i][0], cilpEdge[i][1]))" << std::endl; 
                if (isPointInsideClip(current_point, 512, 512)){
                    //std::cout << "if (isPointInsideClip(current_point, 512, 512))" << std::endl; 
                    if (!isPointInsideClip(perv_point, 512, 512)){
                        //std::cout << "if (!isPointInsideClip(perv_point, 512, 512))" << std::endl; 
                        returntriangle.push_back(Intersecting_point);
 
                    }
                    returntriangle.push_back(current_point);

                }
                if (isPointInsideClip(perv_point, 512, 512)){
                    //std::cout << "if (isPointInsideClip(perv_point, 512, 512))" << std::endl; 
                    returntriangle.push_back(Intersecting_point);
                }

            }
        }
    }
    for (int i = 0; i < returntriangle.size(); i++){
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawPoint(renderer, returntriangle[i].get(0), returntriangle[i].get(1));

    }
    if (returntriangle.size() == 3){ 
        DrawLine(renderer, returntriangle[0], returntriangle[1]);
        DrawLine(renderer, returntriangle[0], returntriangle[2]);
        DrawLine(renderer, returntriangle[1], returntriangle[2]);
    }
    //
    // Rewrite send triangle points
    //
    /*if (returntriangle.size() == 3){
        Triangle cliptrig(renderer, returntriangle[0], returntriangle[1], returntriangle[2]);
        cliptrig.Render();
    }*/
    //cliptrig.Unwrap();
}
