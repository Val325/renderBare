template <class TypeNum>
class Vec2{
    private:
        TypeNum vector[2];
        int size;
    public:
        Vec2(){
            vector[2] = { 0 };
            memset(vector, 0, sizeof vector);
        }
        Vec2(TypeNum one, TypeNum two){
            vector[0] = one;
            vector[1] = two;
            size = 2;
        }
        void set(int i, TypeNum number){
            vector[i] = number;
        }
        TypeNum get(int i){
            return vector[i];
        }
        void increment(int i){
            vector[i] = vector[i]++;
        }
        int sizeVec(){
            return size;
        }
        void show(){
            for (int i = 0; i < size; i++){
                std::cout << vector[i] << " ";
            }
            std::cout << "\n";
        }
        Vec2<TypeNum> operator-(Vec2<TypeNum> &vec2)
        {
            TypeNum res[2];
            res[0] = res[0] - vec2.get(0);
            res[1] = res[1] - vec2.get(1);
            Vec2 vectorNew(res[0], res[1]);
            return vectorNew; 
        }
        Vec2<TypeNum> operator+(Vec2<TypeNum> &vec2)
        {
            TypeNum res[2];
            res[0] = res[0] + vec2.get(0);
            res[1] = res[1] + vec2.get(1);
            Vec2 vectorNew(res[0], res[1]);
            return vectorNew; 
        }
};

template <class TypeNum>
class Vec3{
    private:
        TypeNum vector[3];
        int size;
    public:
        Vec3(){
            vector[3] = { 0 };
            memset(vector, 0, sizeof vector);
        }
        Vec3(TypeNum one, TypeNum two, TypeNum three){
            vector[0] = one;
            vector[1] = two;
            vector[2] = three;
            size = 3;

        }
        void set(int i, TypeNum number){
            vector[i] = number;
        }
        TypeNum get(int i){
            return vector[i];
        }
        int sizeVec(){
            return size;
        }
        void show(){
            for (int i = 0; i < size; i++){
                std::cout << vector[i] << " ";
            }
            std::cout << "\n";
        }
        Vec2<TypeNum> get_screen_coords(){
            TypeNum x = ((vector[0] + 1.0f) * 0.5f) * widthWindow;
            TypeNum y = ((vector[1] + 1.0f) * 0.5f) * heightWindow;
            Vec2<TypeNum> pos(x, y);
            return pos;
        }
        Vec3<TypeNum> operator-(Vec3<TypeNum> &vec2)
        {
            TypeNum res[3];
            res[0] = res[0] - vec2.get(0);
            res[1] = res[1] - vec2.get(1);
            res[2] = res[2] - vec2.get(2);
            Vec3<TypeNum> vectorNew(res[0], res[1], res[2]);
            return vectorNew; 
        }
        Vec3<TypeNum> operator+(Vec3<TypeNum> &vec2)
        {
            TypeNum res[3];
            res[0] = res[0] + vec2.get(0);
            res[1] = res[1] + vec2.get(1);
            res[2] = res[2] + vec2.get(2);
            Vec3<TypeNum> vectorNew(res[0], res[1], res[2]);
            return vectorNew; 
        }

};

template <class TypeNum>
class Vec4{
    private:
        TypeNum vector[4];
        int size;
    public:
        Vec4(){
            vector[4] = { 0 };
            memset(vector, 0, sizeof vector);

        }
        Vec4(TypeNum one, TypeNum two, TypeNum three, TypeNum four){
            vector[0] = one;
            vector[1] = two;
            vector[2] = three;
            vector[3] = four;
            size = 4;
        }
        Vec4(TypeNum res[4]){
            vector[0] = res[0];
            vector[1] = res[1];
            vector[2] = res[2];
            vector[3] = res[3];
            size = 4;
        }
        void set(int i, TypeNum number){
            vector[i] = number;
        }
        TypeNum get(int i){
            return vector[i];
        }
        int sizeVec(){
            return size;
        }
        Vec3<TypeNum> get_Vec3(){
            TypeNum res[3];
            res[0] = vector[0]; 
            res[1] = vector[1];  
            res[2] = vector[2];
        
            Vec3<TypeNum> vectorNew(res[0], res[1], res[2]);
            return vectorNew; 
        }
        Vec3<TypeNum> get_NDC(){
            TypeNum res[3];
            res[0] = vector[0] / vector[3]; 
            res[1] = vector[1] / vector[3];  
            res[2] = vector[2] / vector[3];
            
            /*if (res[2] > 1){
                res[2] = 1.0f;
            }
            
            if (res[2] < -1){
                res[2] = -1.0f;
            }*/
            res[2] = (res[2] + 1.0f) / 2;
            Vec3<TypeNum> vectorNew(res[0], res[1], res[2]);
            return vectorNew; 
        }
        void show(){
            for (int i = 0; i < 4; i++){
                std::cout << vector[i] << " ";
                std::cout << "\n";
            }
        }
        Vec4<TypeNum> operator-(Vec4<TypeNum> &vec2)
        {
            TypeNum res[4];
            res[0] = res[0] - vec2.get(0);
            res[1] = res[1] - vec2.get(1);
            res[2] = res[2] - vec2.get(2);
            res[3] = res[3] - vec2.get(3);
            Vec4<TypeNum> vectorNew(res[0], res[1], res[2], res[3]);
            return vectorNew; 
        }
        Vec4<TypeNum> operator+(Vec4<TypeNum> &vec2)
        {
            TypeNum res[4];
            res[0] = res[0] + vec2.get(0);
            res[1] = res[1] + vec2.get(1);
            res[2] = res[2] + vec2.get(2);
            res[3] = res[3] + vec2.get(3);

            Vec4<TypeNum> vectorNew(res[0], res[1], res[2], res[3]);
            return vectorNew; 
        }
};

class Mat4x4{
    private:
        float mat[4][4];
    public:
        Mat4x4(){
            mat[4][4] = { 0 };
            memset(mat, 0, sizeof mat);

        }
        Mat4x4(float mat00, float mat01, float mat02, float mat03,
               float mat10, float mat11, float mat12, float mat13,
               float mat20, float mat21, float mat22, float mat23,
               float mat30, float mat31, float mat32, float mat33){
            mat[0][0] = mat00, mat[1][0] = mat10, mat[2][0] = mat20, mat[3][0] = mat30;
            mat[0][1] = mat01, mat[1][1] = mat11, mat[2][1] = mat21, mat[3][1] = mat31;
            mat[0][2] = mat02, mat[1][2] = mat12, mat[2][2] = mat22, mat[3][2] = mat32;
            mat[0][3] = mat03, mat[1][3] = mat13, mat[2][3] = mat23, mat[3][3] = mat33;
        }
        Mat4x4(float matrix[4][4]){
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    mat[i][j] = matrix[i][j];
                }
            }        
        }
        float get(int i, int j){
            return mat[i][j];
        }
        void set(int i, int j, float number){
            mat[i][j] = number;
        }
        void show(){
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    std::cout << mat[i][j] << " ";
                }
                std::cout << "\n";
            }
        }
        Vec4<float> multiplyVec4(Vec4<float> vector){
            float res[4] = {0, 0, 0, 0};
            
            res[0] = mat[0][0] * vector.get(0) + mat[0][1] * vector.get(1) + mat[0][2] * vector.get(2) + mat[0][3] * vector.get(3); 
            res[1] = mat[1][0] * vector.get(0) + mat[1][1] * vector.get(1) + mat[1][2] * vector.get(2) + mat[1][3] * vector.get(3);
            res[2] = mat[2][0] * vector.get(0) + mat[2][1] * vector.get(1) + mat[2][2] * vector.get(2) + mat[2][3] * vector.get(3);
            res[3] = mat[3][0] * vector.get(0) + mat[3][1] * vector.get(1) + mat[3][2] * vector.get(2) + mat[3][3] * vector.get(3); 
            Vec4<float> vectorOutput(res);
            return vectorOutput; 
        }
        Mat4x4 operator*(Mat4x4 &mat2)
        {
            float res[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    res[i][j] = 0;
                    for (int k = 0; k < 4; k++) {
                        res[i][j] += mat[i][k] * mat2.get(k, j);
                    }
                }
            }


            Mat4x4 multipleMat(res);
            return multipleMat;
        }
};
