#include <limits>
#include <cmath>

double Dot(Vec2<double> v1, Vec2<double> v2) {
    double result = 0;
    for (int i = 0; i < v1.sizeVec(); ++i) {
        result += v1.get(i) * v2.get(i);
    }
    return result;
}

Vec3<double> Barycentric(Vec2<double> p, Vec2<float> a, Vec2<float> b, Vec2<float> c)
{
    Vec2<double> aDouble(a.get(0), a.get(1)); 
    Vec2<double> bDouble(b.get(0), b.get(1)); 
    Vec2<double> cDouble(c.get(0), c.get(1)); 

    Vec2<double> v0 = bDouble - aDouble, v1 = cDouble - aDouble, v2 = p - aDouble;
    double d00 = Dot(v0, v0);
    double d01 = Dot(v0, v1);
    double d11 = Dot(v1, v1);
    double d20 = Dot(v2, v0);
    double d21 = Dot(v2, v1);
    double denom = d00 * d11 - d01 * d01;

    double res[3];
    // v = (d11 * d20 - d01 * d21) / denom
    res[0] = (d11 * d20 - d01 * d21) / denom;
    // w = (d00 * d21 - d01 * d20) / denom;
    res[1] = (d00 * d21 - d01 * d20) / denom;
    //u = 1.0f - v - w; 
    res[2] = 1.0f - res[0] - res[1];
    
    Vec3<double> vectorNew(res[0], res[1], res[2]);
    return vectorNew; 
}

/*inline float dotProduct(Vec3 vecA, Vec3 vecB)
{
    return vecA.get(0) * vecB.get(0) + vecA.get(1) * vecB.get(1) + vecA.get(2) * vecB.get(2);
}


Vec3 crossProduct(Vec3 vecA, Vec3 vecB)
{
    
    float x = vecA.get(1) * vecB.get(2) - vecA.get(2) * vecB.get(1);
    float y = vecA.get(2) * vecB.get(0) - vecA.get(0) * vecB.get(2);
    float z = vecA.get(0) * vecB.get(1) - vecA.get(1) * vecB.get(0);
    Vec3 crossP(x, y, z);
    return crossP; 
}

float magnitude(Vec3 vec){
    return sqrt(vec.get(0) * vec.get(0) + vec.get(1) * vec.get(1) + vec.get(2) * vec.get(2)); 
}



//https://ceng2.ktu.edu.tr/~cakir/files/grafikler/Texture_Mapping.pdf
Vec3 calculateBarycentricCoords(Vec2 vec0, Vec2 vec1, Vec2 vec2, Vec2 pixel){
    Vec3 coords;

    Vec3 normalTriangle = crossProduct(vec1 - vec0, vec2 - vec0);
    Vec3 normalA = crossProduct(vec2 - vec1, pixel - vec1);
    Vec3 normalB = crossProduct(vec0 - vec2, pixel - vec2);
    Vec3 normalC = crossProduct(vec1 - vec0, pixel - vec0);
    
    float a;
    float b;
    float y;
    if (magnitude(normalTriangle)*magnitude(normalTriangle) != 0){
        a = (dotProduct(normalTriangle, normalA))/(magnitude(normalTriangle)*magnitude(normalTriangle)); 
        b = (dotProduct(normalTriangle, normalB))/(magnitude(normalTriangle)*magnitude(normalTriangle));
        y = (dotProduct(normalTriangle, normalC))/(magnitude(normalTriangle)*magnitude(normalTriangle));
    }

    return coords; 
}*/

#include "primitive/line.cpp"
#include "primitive/triangle.cpp"
#include "utils/intersection.cpp"
/*class Triangle{
    public:
        Triangle(SDL_Renderer *rend, Vec3 Vert1, Vec3 Vert2, Vec3 Vert3);
        void Projection();
        void Clip(std::vector<std::vector<Vec2>> cilp);
        void Unwrap();
        void Render();
};*/
void SutherlandHodgman(SDL_Renderer *renderer,Vec2<float> point1, Vec2<float> point2, Vec2<float> point3, std::vector<std::vector<Vec2<float>>> cilpEdge);
std::vector<Vec4<float>> loadObj(std::string path);

Vec2<float> ViewportToCanvas(float x, float y){

    float xCanv = (x * widthWindow)/widthViewport;
    float yCanv = (y * heightWindow)/heightViewport;
    Vec2<float> pos(xCanv, yCanv); 
    return pos;
}
Vec2<float> ProjectVertex(Vec3<float> v){

    Vec2<float> pos = ViewportToCanvas(
            (v.get(0) * NearDistance) / -v.get(2), 
            (v.get(1) * NearDistance) / -v.get(2)); 
    return pos; 
}


//template <class Vec>
inline float edgeFunction(Vec3<float> a, Vec3<float> b, Vec3<float> c) {
    return (c.get(0) - a.get(0)) * (b.get(1) - a.get(1)) - (c.get(1) - a.get(1)) * (b.get(0) - a.get(0));
}





//find min vector
// posTriangle is position
// elemVec is element vector
float minVector(std::vector<Vec4<float>> posTriange, int elemVec){
    // Assume first element as minimum
    float min = posTriange[0].get(elemVec);
    for (int i = 1; i < posTriange.size(); i++) {
      
      	// Update m if arr[i] is smaller
        if (posTriange[i].get(elemVec) < min) {
            min = posTriange[i].get(elemVec); 
        }
    }
    return min;
}

std::vector<std::string> tokenize(std::string str, char delim){
    std::vector<std::string> tokens;
    std::string temp = "";
    for(int i = 0; i < str.length(); i++){
        if(str[i] == delim){
            tokens.push_back(temp);
            temp = "";
        }
        else
            temp += str[i];           
    }
    tokens.push_back(temp);
    return tokens;
}

/* A utility function to calculate area of triangle formed by (x1, y1), 
   (x2, y2) and (x3, y3) */
float area(float x1, float y1, float x2, float y2, float x3, float y3)
{
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}
  
/* A function to check whether point P(x, y) lies inside the triangle formed 
   by A(x1, y1), B(x2, y2) and C(x3, y3) */
bool isInside(float x1, float y1, float x2, float y2, float x3, float y3, float x, float y)
{   
   /* Calculate area of triangle ABC */
   float A = area (x1, y1, x2, y2, x3, y3);
  
   /* Calculate area of triangle PBC */ 
   float A1 = area (x, y, x2, y2, x3, y3);
  
   /* Calculate area of triangle PAC */ 
   float A2 = area (x1, y1, x, y, x3, y3);
  
   /* Calculate area of triangle PAB */  
   float A3 = area (x1, y1, x2, y2, x, y);
    
   /* Check if sum of A1, A2 and A3 is same as A */
   return (A == A1 + A2 + A3);
}

bool isTriangleDrawn(Vec2<float> ScreenVertex01,Vec2<float> ScreenVertex02,Vec2<float> ScreenVertex03){
    bool firstVertex = false;
    bool firstVertex1 = false;
    bool firstVertex2 = false;
    bool firstVertex3 = false;
    bool firstVertex4 = false;

    if (ScreenVertex01.get(0) > 0){
        firstVertex1 = true; 
    }
    if (ScreenVertex01.get(1) > 0){
        firstVertex2 = true;     
    }
    if (ScreenVertex01.get(0) < 512){
        firstVertex3 = true; 
    }
    if (ScreenVertex01.get(1) < 512){
        firstVertex4 = true; 
    }
    firstVertex = firstVertex1 && firstVertex2 && firstVertex3 && firstVertex4; 

    bool secondVertex = false;
    bool secondVertex1 = false;
    bool secondVertex2 = false;
    bool secondVertex3 = false;
    bool secondVertex4 = false;

    if (ScreenVertex02.get(0) > 0){
        secondVertex1 = true; 
    }
    if (ScreenVertex02.get(1) > 0){
        secondVertex2 = true;  
    }
    if (ScreenVertex02.get(0) < 512){
        secondVertex3 = true;     
    }
    if (ScreenVertex02.get(1) < 512){
        secondVertex4 = true; 
    }
    secondVertex = secondVertex1 && secondVertex2 && secondVertex3 && secondVertex4;

    bool thirdVertex = false;
    bool thirdVertex1 = false;
    bool thirdVertex2 = false;
    bool thirdVertex3 = false;
    bool thirdVertex4 = false;

    if (ScreenVertex03.get(0) > 0){
        thirdVertex1 = true; 
    }
    if (ScreenVertex03.get(1) > 0){
        thirdVertex2 = true;  
    }
    if (ScreenVertex03.get(0) < 512){
        thirdVertex3 = true; 
    }
    if (ScreenVertex03.get(1) < 512){
        thirdVertex4 = true; 
    }
    thirdVertex = thirdVertex1 && thirdVertex2 && thirdVertex3 && thirdVertex4; 
    return  firstVertex && secondVertex && thirdVertex; 
}

class Triangle{
    private:
        SDL_Renderer *renderer;
        bool isRender;
        float zDistance;
        Vec3<float> MidPoint;

        // 4 dimension coordinate
        Vec4<float> Vertex01Homogen;
        Vec4<float> Vertex02Homogen;
        Vec4<float> Vertex03Homogen;
        
        // 3 dimension coordinate
        Vec3<float> Vertex01;
        Vec3<float> Vertex02;
        Vec3<float> Vertex03;
        Vec3<float> Coord01;
        Vec3<float> Coord02;
        Vec3<float> Coord03;
        
        //texture coordinate
        Vec2<float> st2;
        Vec2<float> st1;
        Vec2<float> st0;

        Vec2<float> ScreenVertex01;
        Vec2<float> ScreenVertex02;
        Vec2<float> ScreenVertex03;
        cimg_library::CImg<unsigned char> texture;
        triangleInfo trig_struct;
        Mat4x4 PV;
    public:
        Triangle(SDL_Renderer *rend, Vec4<float> Vert1, Vec4<float> Vert2, Vec4<float> Vert3){
            renderer = rend;
            Vertex01Homogen = Vert1;
            Vertex02Homogen = Vert2;
            Vertex03Homogen = Vert3;
            isRender = true;

            Vec3 centerTiangle((Vert1.get(0) + Vert2.get(0) + Vert3.get(0))/3, 
                    (Vert1.get(1) + Vert2.get(1) + Vert3.get(1))/3, 
                    (Vert1.get(2) + Vert2.get(2) + Vert3.get(2))/3);
            MidPoint = centerTiangle; 

            //zDistance =
            Vec3<float> c2(1, 0, 0);
            Coord03 = c2;
            
            Vec3<float> c1(0, 1, 0);
            Coord02 = c1;

            Vec3<float> c0(0, 0, 1);
            Coord01 = c0;

            st2 = Vec2<float>(0, 0);
            st1 = Vec2<float>(1, 0);
            st0 = Vec2<float>(0, 1);

        }
        Triangle(SDL_Renderer *rend, Vec3<float> Vert1, Vec3<float> Vert2, Vec3<float> Vert3){
            renderer = rend;
            Vertex01 = Vert1;
            Vertex02 = Vert2;
            Vertex03 = Vert3;

            Vec3<float> c2(1, 0, 0);
            Coord03 = c2;
            
            Vec3<float> c1(0, 1, 0);
            Coord02 = c1;

            Vec3<float> c0(0, 0, 1);
            Coord01 = c0;

            st2 = Vec2<float>(0, 0);
            st1 = Vec2<float>(1, 0);
            st0 = Vec2<float>(0, 1);
            cimg_library::CImg<unsigned char> src("src/chess.png"); 
            texture = src;
            //std::cout << "height: " << texture.height() << std::endl; 
        }
        Triangle(SDL_Renderer *rend, Vec2<float> Vert1, Vec2<float> Vert2, Vec2<float> Vert3){
            renderer = rend;
            ScreenVertex01 = Vert1;
            ScreenVertex02 = Vert2;
            ScreenVertex03 = Vert3;

            Vec3<float> c2(1, 0, 0);
            Coord03 = c2;
            
            Vec3<float> c1(0, 1, 0);
            Coord02 = c1;

            Vec3<float> c0(0, 0, 1);
            Coord01 = c0;

            st2 = Vec2<float>(0, 0);
            st1 = Vec2<float>(1, 0);
            st0 = Vec2<float>(0, 1);
            cimg_library::CImg<unsigned char> src("src/chess.png"); 
            texture = src;
            //std::cout << "height: " << texture.height() << std::endl; 
        }
        void Projection(Mat4x4 projetion, Mat4x4 camera, Mat4x4 transform, Vec3<float> startPos){
            //ScreenVertex01 = ProjectVertex(Vertex01);
            //ScreenVertex02 = ProjectVertex(Vertex02);
            //ScreenVertex03 = ProjectVertex(Vertex03);
            PV = projetion * camera * transform;
            Vec4<float> proj_pos1 = PV.multiplyVec4(Vertex01Homogen);
            Vec3<float> pos1_NDC = proj_pos1.get_NDC();
            ScreenVertex01 = pos1_NDC.get_screen_coords();
            
            Vec3<float> pos1 = Vertex01Homogen.get_Vec3();
            //std::cout << "pos1: " << std::endl;            
            //pos1.show();
            Vec3<float> pos2 = Vertex02Homogen.get_Vec3();
            //std::cout << "pos2: " << std::endl;            
            //pos2.show();
            Vec3<float> pos3 = Vertex03Homogen.get_Vec3();
            //std::cout << "pos3: " << std::endl;
            //pos3.show();
            //std::cout << "startPos: " << std::endl;
            //startPos.show();
            //std::vector<Vec4> posTriangeAll;
            //posTriangeAll.push_back(Vertex01Homogen);
            //posTriangeAll.push_back(Vertex02Homogen);
            //posTriangeAll.push_back(Vertex03Homogen);
            //float posrender = minVector(posTriangeAll, 2);
            //std::cout << "z: " << startPos.get(2) << std::endl;
            //std::cout << "pos z: " << posrender << std::endl; 
            
            /*if (startPos.get(2) > -Vertex01Homogen.get(2)
                & startPos.get(2) > -Vertex02Homogen.get(2)
                & startPos.get(2) > -Vertex03Homogen.get(2)){
                isRender = true;
            }else{
                isRender = false;        
            }*/

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

            Vec4<float> proj_pos2 = PV.multiplyVec4(Vertex02Homogen);
            Vec3<float> pos2_NDC = proj_pos2.get_NDC();
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

            Vec4<float> proj_pos3 = PV.multiplyVec4(Vertex03Homogen);
            Vec3<float> pos3_NDC = proj_pos3.get_NDC();
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
        void rotation(float alpha, float beta, float gamma){
            Mat4x4 Rotation(
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0 
            );
        }
        void transform(Vec3<float> Newposition){
            Mat4x4 Transformation(
                1, 0, 0, Newposition.get(0),
                0, 1, 0, Newposition.get(1),
                0, 0, 1, Newposition.get(2),
                0, 0, 0, 1 
            );
            PV = PV * Transformation; 
        }
        void Clip(std::vector<std::vector<Vec2<float>>> cilp){
            if (isRender){
                SutherlandHodgman(renderer, ScreenVertex01, ScreenVertex02, ScreenVertex03, cilp);
            }
        }
        void Zbuffer(double **z_buffer, Vec3<float> startPos){
            //Vec3 DistanceZ = MidPoint - startPos;
            //float DistanceZ = sqrt(pow(MidPoint.get(0) - startPos.get(0),2)+pow(MidPoint.get(1) - startPos.get(1),2)+pow(MidPoint.get(2) - startPos.get(2),2));
            //float DistanceZ = 0;
            //zDistance = DistanceZ;

            
            /*if (isTriangleDrawn(ScreenVertex01,ScreenVertex02,ScreenVertex03)){
                for (int x = 0;x < 512; x++){
                    for (int y = 0;y < 512; y++){
                        if (isInside(ScreenVertex01.get(0), ScreenVertex01.get(1), 
                                    ScreenVertex02.get(0), ScreenVertex02.get(1), 
                                    ScreenVertex03.get(0), ScreenVertex03.get(1), 
                                    x, y)){
                            Vec2 point(x, y); 
                            Vec3 baricentric = Barycentric(point, ScreenVertex01, ScreenVertex02, ScreenVertex03);
                            baricentric.show();
                        }
                    }
                }
            }*/
        }
        void Unwrap(double **z_buffer){
            
            trig_struct.vert1 = Vertex01; 
            trig_struct.vert2 = Vertex02;
            trig_struct.vert3 = Vertex03;
            trig_struct.ScreenVert1 = ScreenVertex01; 
            trig_struct.ScreenVert2 = ScreenVertex02;
            trig_struct.ScreenVert3 = ScreenVertex03;

            DrawTriangle(renderer, ScreenVertex01, ScreenVertex02, ScreenVertex03, z_buffer, trig_struct);
        }
        void WrapTexture(double **z_buffer){
            //DrawTriangle(renderer, ScreenVertex01, ScreenVertex02, ScreenVertex03);

            //
        }
        void Show(){
            std::cout << "triangle: " << std::endl;
            Vertex01Homogen.show();
            Vertex02Homogen.show();
            Vertex03Homogen.show();
            std::cout << "----------------" << std::endl;

        }
        void Render(double **z_buffer){
            /*struct triangleInfo{
                Vec3 vert1;
                Vec3 vert2;
                Vec3 vert3;
            };*/
            trig_struct.vert1 = Vertex01; 
            trig_struct.vert2 = Vertex02;
            trig_struct.vert3 = Vertex03;
            trig_struct.ScreenVert1 = ScreenVertex01; 
            trig_struct.ScreenVert2 = ScreenVertex02;
            trig_struct.ScreenVert3 = ScreenVertex03;

            if (isRender){
                DrawLine(renderer, ScreenVertex01, ScreenVertex02, z_buffer,  trig_struct);
                DrawLine(renderer, ScreenVertex01, ScreenVertex03, z_buffer,  trig_struct);
                DrawLine(renderer, ScreenVertex02, ScreenVertex03, z_buffer,  trig_struct);
            }
        }

};

std::vector<Triangle> loadObj(SDL_Renderer *rend, std::string path){
    std::ifstream file_model(path);
    std::vector<std::pair<Vec4<float>, int>> obj_verticies;
    std::vector<Triangle> faces;

    if (!file_model.is_open()) {
        std::cerr << "Error opening the file!";
    }
    std::string file_model_data;
    int numVertex = 1;
    while (std::getline(file_model, file_model_data))
    {
        std::vector<std::string> data_model = tokenize(file_model_data, ' ');
        //std::cout << data_model[0] << std::endl;
        if (data_model[0].compare("v") == 0){
            std::pair<Vec4<float>, int> VertexData;
             
            std::cout << "vertex: " << data_model[1] << " " << data_model[2] << " " << data_model[3] << std::endl;
            Vec4 Vertex(std::stof(data_model[1]), std::stof(data_model[2]), std::stof(data_model[3]), 1.0f);
            VertexData.first = Vertex;
            VertexData.second = numVertex;
            //Triangle trig(rend, data_model[1], data_model[2], data_model[3]);
            obj_verticies.push_back(VertexData);
            numVertex++;
        }
        if (data_model[0].compare("f") == 0){

            Vec4<float> Vertex1;
            Vec4<float> Vertex2;
            Vec4<float> Vertex3;
            //std::cout << "file: " << data_model[1] << " " << data_model[2] << " " << data_model[3] << std::endl; 
            for (int i = 0; i < obj_verticies.size();i++){
                


                if (obj_verticies[i].second == std::stoi(data_model[1])){
                    /*std::cout << "vertex id: " << obj_verticies[i].second << std::endl;
                    std::cout << "vertex: " << obj_verticies[i].first.get(0) << " " << obj_verticies[i].first.get(1) << " " << obj_verticies[i].first.get(2) << std::endl; 
                    std::cout << "data_model: " << data_model[1] << std::endl; 
                    */
                    Vertex1 = obj_verticies[i].first; 
                }
                if (obj_verticies[i].second == std::stoi(data_model[2])){
                    /*std::cout << "vertex id: " << obj_verticies[i].second << std::endl;
                    std::cout << "vertex: " << obj_verticies[i].first.get(0) << " " << obj_verticies[i].first.get(1) << " " << obj_verticies[i].first.get(2) << std::endl; 
                    std::cout << "data_model: " << data_model[2] << std::endl; 
                    */
                    Vertex2 = obj_verticies[i].first;
                }
                if (obj_verticies[i].second == std::stoi(data_model[3])){
                    /*std::cout << "vertex id: " << obj_verticies[i].second << std::endl;
                    std::cout << "vertex: " << obj_verticies[i].first.get(0) << " " << obj_verticies[i].first.get(1) << " " << obj_verticies[i].first.get(2) << std::endl; 
                    std::cout << "data_model: " << data_model[3] << std::endl; 
                    */
                    Vertex3 = obj_verticies[i].first;
                }
            }
            Triangle trig(rend, Vertex1, Vertex2, Vertex3);
            faces.push_back(trig);
            
        }
    }
    /*for (int i = 0; i < faces.size();){
        faces[i].Show();
    }*/
    return faces;
}

void SutherlandHodgman(SDL_Renderer *renderer,Vec2<float> point1, Vec2<float> point2, Vec2<float> point3, std::vector<std::vector<Vec2<float>>> cilpEdge){
    std::vector<Vec2<float>> output;
    output.push_back(point1);
    output.push_back(point2);
    output.push_back(point3);

    std::vector<Vec2<float>> returntriangle;

    for (int i = 0; i < cilpEdge.size(); i++){


        for (int j = 0; j < output.size(); j++){
            Vec2<float> current_point = output[j];
            //Vec2 perv_point = output[(j-1)%output.size()];
            Vec2<float> perv_point;
            if ((j-1) < 0){
                perv_point = output[output.size()-1];
            }else{
                perv_point = output[j-1];
            }

            if (isLineIntersect(perv_point, current_point,cilpEdge[i][0], cilpEdge[i][1])) {
                Vec2<float> Intersecting_point = isLineIntersectPos(perv_point, current_point, cilpEdge[i][0], cilpEdge[i][1]);
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
    /*for (int i = 0; i < returntriangle.size(); i++){
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawPoint(renderer, returntriangle[i].get(0), returntriangle[i].get(1));

    }
    if (returntriangle.size() == 3){ 
        DrawLine(renderer, returntriangle[0], returntriangle[1]);
        DrawLine(renderer, returntriangle[0], returntriangle[2]);
        DrawLine(renderer, returntriangle[1], returntriangle[2]);
    }*/
    //std::cout << "size triangle: " << returntriangle.size();
    //
    // Rewrite send triangle points
    //
    /*if (returntriangle.size() == 3){
        Triangle cliptrig(renderer, returntriangle[0], returntriangle[1], returntriangle[2]);
        cliptrig.Render();
    }*/
    //cliptrig.Unwrap();
}
