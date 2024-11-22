
class Vec2{
    private:
        float vector[2];
    public:
        Vec2(){
            vector[2] = { 0 };
            memset(vector, 0, sizeof vector);
        }
        Vec2(float one, float two){
            vector[0] = one;
            vector[1] = two;

        }
        void set(int i, float number){
            vector[i] = number;
        }
        float get(int i){
            return vector[i];
        }
        void increment(int i){
            vector[i] = vector[i]++;
        }
};

class Vec3{
    private:
        float vector[3];
    public:
        Vec3(){
            vector[3] = { 0 };
            memset(vector, 0, sizeof vector);
        }
        Vec3(float one, float two, float three){
            vector[0] = one;
            vector[1] = two;
            vector[2] = three;

        }
        void set(int i, float number){
            vector[i] = number;
        }
        float get(int i){
            return vector[i];
        }
};

class Vec4{
    private:
        float vector[4];
    public:
        Vec4(){
            vector[4] = { 0 };
            memset(vector, 0, sizeof vector);

        }
        Vec4(float one, float two, float three, float four){
            vector[0] = one;
            vector[1] = two;
            vector[2] = three;
            vector[3] = four;

        }
        void set(int i, float number){
            vector[i] = number;
        }
        float get(int i){
            return vector[i];
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
            mat[4][4] = matrix[4][4];
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
        Mat4x4 operator*(Mat4x4 &mat2)
        {
            float res[4][4];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < 4; k++) {
                        res[i][j] += mat[i][k] * mat2.get(k, j);
                    }
                }
            }
            Mat4x4 multipleMat(res);
            return multipleMat;
        }
};
