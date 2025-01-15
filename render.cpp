#include <limits>
#include <cmath>

double Dot(Vec2<double> v1, Vec2<double> v2) {
    double result = 0;
    for (int i = 0; i < v1.sizeVec(); ++i) {
        result += v1.get(i) * v2.get(i);
    }
    return result;
}

float Dot(Vec3<float> v1, Vec3<float> v2) {
    float result = 0;
    for (int i = 0; i < v1.sizeVec(); ++i) {
        result += v1.get(i) * v2.get(i);
    }
    return result;
}
float Dot(Vec2<float> v1, Vec2<float> v2) {
    float result = 0;
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

Vec3<float> Barycentric(Vec2<float> p, Vec2<float> a, Vec2<float> b, Vec2<float> c)
{
    Vec2<float> aDouble(a.get(0), a.get(1)); 
    Vec2<float> bDouble(b.get(0), b.get(1)); 
    Vec2<float> cDouble(c.get(0), c.get(1)); 

    Vec2<float> v0 = bDouble - aDouble, v1 = cDouble - aDouble, v2 = p - aDouble;
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
    
    Vec3<float> vectorNew(res[0], res[1], res[2]);
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

Vec3<float> CrossProduct(Vec3<float> b, Vec3<float> c){
    //std::cout << "b: " << std::endl;
    //b.show();
    //std::cout << "c: " << std::endl;
    //c.show();

    float x = b.get(1)*c.get(2) - b.get(2)*c.get(1); 
    float y = b.get(2)*c.get(0) - b.get(0)*c.get(2);
    float z = b.get(0)*c.get(1) - b.get(1)*c.get(0);
    
    Vec3<float> crossVector(x, y, z);
    return crossVector; 
}

class Triangle{
    private:
        SDL_Renderer *renderer;
        bool isRender;
        bool isUseTexture;
        bool UseZbuffer;
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


        Vec3<float> NormalTriangle;

        //texture coordinate
        Vec2<float> st2;
        Vec2<float> st1;
        Vec2<float> st0;

        Vec2<float> ScreenVertex01;
        Vec2<float> ScreenVertex02;
        Vec2<float> ScreenVertex03;
        
        triangleInfo trig_struct;
        Mat4x4 PV;
        Mat4x4 Camera_m;
        Mat4x4 Rotation_m;
        Mat4x4 Projection_m;
        Mat4x4 Transformation_m;
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
            Vec3<float> statPoint(0, 0, 0);

            Vec2<float> tex1(0, 0);
            st2 = tex1;
            Vec2<float> tex2(1, 0);
            st1 = tex2; 
            Vec2<float> tex3(0, 1);
            st0 = tex3;
        }
        Triangle(SDL_Renderer *rend, Vec3<float> Vert1, Vec3<float> Vert2, Vec3<float> Vert3){
            renderer = rend;
            Vertex01 = Vert1;
            Vertex02 = Vert2;
            Vertex03 = Vert3;

            st2 = Vec2<float>(0, 0);
            st1 = Vec2<float>(1, 0);
            st0 = Vec2<float>(0, 1);
        }
        Triangle(SDL_Renderer *rend, Vec2<float> Vert1, Vec2<float> Vert2, Vec2<float> Vert3){
            renderer = rend;
            ScreenVertex01 = Vert1;
            ScreenVertex02 = Vert2;
            ScreenVertex03 = Vert3;

            st2 = Vec2<float>(0, 0);
            st1 = Vec2<float>(1, 0);
            st0 = Vec2<float>(0, 1);

        }
        void Projection(){
            float aspect_ratio = widthWindow / heightWindow;
            float scale = 1 / tan(angleOfView * 0.5 * PI / 180);
            float aspect_scale = 1 / (tan(angleOfView * 0.5 * PI / 180) * aspect_ratio);
            float depth_norm = -(far+near) / (far-near);
            float depth_norm2 = -2*far*near / (far-near);

            //https://medium.com/@jrespinozah/3d-graphics-the-perspective-projection-d2076f42cdf3
            Mat4x4 ProjectionMat(
                aspect_scale, 0, 0, 0,
                0, scale, 0, 0,
                0, 0, depth_norm, depth_norm2,
                0, 0, 1, 0 
            );
            Projection_m = ProjectionMat; 
        }
        void View(Vec3<float> cameraPos){
            //https://medium.com/@carmencincotti/lets-look-at-magic-lookat-matrices-c77e53ebdf78
            Mat4x4 CameraMat(
                0.0f, 0.0f, 1.0f, -cameraPos.get(0),
                0.0f, -1.0f, 0.0f, -cameraPos.get(1),
                1.0f, 0.0f, 0.0f, -cameraPos.get(2),
                0.0f, 0.0f, 0.0f, 1.0f 
            );
            Camera_m = CameraMat; 
        }
        void Rotatition(float a, float b, float g){
            Mat4x4 RotationMat(
                cos(degreeToRadian(a))*cos(degreeToRadian(b)), cos(degreeToRadian(a))*sin(degreeToRadian(b))*sin(degreeToRadian(g))-sin(degreeToRadian(a))*cos(degreeToRadian(g)), cos(degreeToRadian(a))*sin(degreeToRadian(b))*cos(degreeToRadian(g))+sin(degreeToRadian(a))*sin(degreeToRadian(g)), 0,
                sin(degreeToRadian(a))*cos(degreeToRadian(b)), sin(degreeToRadian(a))*sin(degreeToRadian(b))*sin(degreeToRadian(g))+cos(degreeToRadian(a))*cos(degreeToRadian(g)), sin(degreeToRadian(a))*sin(degreeToRadian(b))*cos(degreeToRadian(g))-cos(degreeToRadian(a))*sin(degreeToRadian(g)), 0,
                -sin(degreeToRadian(b)), cos(degreeToRadian(b))*sin(degreeToRadian(g)), cos(degreeToRadian(b))*cos(degreeToRadian(g)), 0,
                0, 0, 0, 1 
            );
            Rotation_m = RotationMat; 
        }

        void Transform(Vec3<float> Newposition){
            Mat4x4 TransformationMat(
                1, 0, 0, Newposition.get(0),
                0, 1, 0, Newposition.get(1),
                0, 0, 1, Newposition.get(2),
                0, 0, 0, 1 
            );
            Transformation_m = TransformationMat; 
        }
        void Transform(float x, float y, float z){
            Mat4x4 TransformationMat(
                1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, z,
                0, 0, 0, 1 
            );
            Transformation_m = TransformationMat; 
        }
        void Apply(){
            PV = Projection_m * Camera_m * Transformation_m * Rotation_m;

            Vec4<float> proj_pos1 = PV.multiplyVec4(Vertex01Homogen);
            Vec3<float> pos1_NDC = proj_pos1.get_NDC();
            ScreenVertex01 = pos1_NDC.get_screen_coords();
            
            Vec3<float> pos1 = Vertex01Homogen.get_Vec3();
            Vec3<float> pos2 = Vertex02Homogen.get_Vec3();
            Vec3<float> pos3 = Vertex03Homogen.get_Vec3();
            
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

        }
        void CullFace(Vec3<float> startPos){
            Vec3 Vec1_3 = Vertex01Homogen.get_Vec3();
            Vec3 Vec2_3 = Vertex02Homogen.get_Vec3();
            Vec3 Vec3_3 = Vertex03Homogen.get_Vec3();
            Vec3 Vec1 = Vec2_3 - Vec1_3;
            Vec3 Vec2 = Vec3_3 - Vec1_3;
            NormalTriangle = CrossProduct(Vec1, Vec2);

            float similarity = Dot(NormalTriangle, startPos);
            if (similarity > 0){
                isRender = false;        
            }else{
                isRender = true;        
            }
        }
        void FixRender(Vec3<float> startPos){
            Vec3<float> zLine(0,0,1);
            float similarity = Dot(MidPoint+zLine, startPos);

            if (similarity > 0){
                isRender = false;        
            }else{
                isRender = true;        
            }
        }
        /*
        void Projection(Mat4x4 projetion, Mat4x4 camera, Mat4x4 transform, Mat4x4 rotate, Vec3<float> startPos){

            PV = projetion * camera * transform * rotate;
            Vec4<float> proj_pos1 = PV.multiplyVec4(Vertex01Homogen);
            Vec3<float> pos1_NDC = proj_pos1.get_NDC();
            ScreenVertex01 = pos1_NDC.get_screen_coords();
            
            Vec3<float> pos1 = Vertex01Homogen.get_Vec3();


            Vec3<float> pos2 = Vertex02Homogen.get_Vec3();


            Vec3<float> pos3 = Vertex03Homogen.get_Vec3();

            
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


    
            Vec3 Vec1_3 = Vertex01Homogen.get_Vec3();
            Vec3 Vec2_3 = Vertex02Homogen.get_Vec3();
            Vec3 Vec3_3 = Vertex03Homogen.get_Vec3();
            Vec3 Vec1 = Vec2_3 - Vec1_3;
            Vec3 Vec2 = Vec3_3 - Vec1_3;
            NormalTriangle = CrossProduct(Vec1, Vec2);

            float similarity = Dot(NormalTriangle, startPos);
            Vec3<float> zLine(0,0,1);
            float similaritZ = Dot(MidPoint+zLine, startPos);

            if (similarity > 0 || similaritZ > 0){
                isRender = false;        
            }else{
                isRender = true;        
            }
        }
        */

        void Clip(std::vector<std::vector<Vec2<float>>> cilp){
            if (isRender){
                SutherlandHodgman(renderer, ScreenVertex01, ScreenVertex02, ScreenVertex03, cilp);
            }
        }
        void isUseZbuffer(bool isSet){
            UseZbuffer = isSet; 
        }
        void isUseZTexture(bool isSet){
            trig_struct.isUseTexture = isSet; 
        }
        void setTexture(std::string str_path){
            cimg_library::CImg<unsigned char> src(str_path.c_str()); 
            trig_struct.texture = src; 
            trig_struct.isUseTexture = false;
        }
        void setTexture(std::string str_path, bool isSet){
            cimg_library::CImg<unsigned char> src(str_path.c_str()); 
            trig_struct.texture = src; 
            trig_struct.isUseTexture = isSet;
        }
        void setTextureCoords(Vec2<float> st0_n, Vec2<float> st1_n, Vec2<float> st2_n){
            st0 = st0_n;
            st1 = st1_n;
            st2 = st2_n;
        }
        void setTextureCoords(float st0_1, float st0_2, float st1_1, float st1_2, float st2_1, float st2_2){
            st0.set(0, st0_1);
            st0.set(1, st0_2);

            st1.set(0, st1_1);
            st1.set(1, st1_2);

            st2.set(0, st2_1);
            st2.set(1, st2_2);
        }
        void Unwrap(double **z_buffer){
            
            trig_struct.vert1 = Vertex01; 
            trig_struct.vert2 = Vertex02;
            trig_struct.vert3 = Vertex03;
            
            trig_struct.st1 = st0; 
            trig_struct.st2 = st1;
            trig_struct.st3 = st2;

            trig_struct.ScreenVert1 = ScreenVertex01; 
            trig_struct.ScreenVert2 = ScreenVertex02;
            trig_struct.ScreenVert3 = ScreenVertex03;
            trig_struct.normal = NormalTriangle;
            if (isRender){
                DrawTriangle(renderer, ScreenVertex01, ScreenVertex02, ScreenVertex03, z_buffer, trig_struct);
            }
        }
        void Debug(){
            std::cout << "triangle: " << std::endl;
            Vertex01Homogen.show();
            Vertex02Homogen.show();
            Vertex03Homogen.show();
            std::cout << "----------------" << std::endl;

        }
        void RenderWireframe(double **z_buffer, Vec3<float> startPos){

            trig_struct.vert1 = Vertex01; 
            trig_struct.vert2 = Vertex02;
            trig_struct.vert3 = Vertex03;
            trig_struct.ScreenVert1 = ScreenVertex01; 
            trig_struct.ScreenVert2 = ScreenVertex02;
            trig_struct.ScreenVert3 = ScreenVertex03;
            trig_struct.normal = NormalTriangle;


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
        if (data_model[0].compare("v") == 0){
            std::pair<Vec4<float>, int> VertexData;
             
            //std::cout << "vertex: " << data_model[1] << " " << data_model[2] << " " << data_model[3] << std::endl;
            Vec4 Vertex(std::stof(data_model[1]), std::stof(data_model[2]), std::stof(data_model[3]), 1.0f);
            VertexData.first = Vertex;
            VertexData.second = numVertex;
            obj_verticies.push_back(VertexData);
            numVertex++;
        }
        if (data_model[0].compare("f") == 0){

            Vec4<float> Vertex1;
            Vec4<float> Vertex2;
            Vec4<float> Vertex3;
            for (int i = 0; i < obj_verticies.size();i++){
                


                if (obj_verticies[i].second == std::stoi(data_model[1])){

                    Vertex1 = obj_verticies[i].first; 
                }
                if (obj_verticies[i].second == std::stoi(data_model[2])){

                    Vertex2 = obj_verticies[i].first;
                }
                if (obj_verticies[i].second == std::stoi(data_model[3])){

                    Vertex3 = obj_verticies[i].first;
                }
            }
            Triangle trig(rend, Vertex1, Vertex2, Vertex3);
            faces.push_back(trig);
            
        }
    }

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
                if (isPointInsideClip(current_point, 512, 512)){
                    if (!isPointInsideClip(perv_point, 512, 512)){
                        returntriangle.push_back(Intersecting_point);
 
                    }
                    returntriangle.push_back(current_point);

                }
                if (isPointInsideClip(perv_point, 512, 512)){
                    returntriangle.push_back(Intersecting_point);
                }

            }
        }
    }

}
