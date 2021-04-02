#include<iostream>
#include<stack>
#include<array>

//class xforms{
//    float x2[2][2];
//public:
//    xforms(float[2][2]){
//        std::copy(&arr[0][0], &arr[0][0]+2*2, &x2[0][0]);
//    }
//}
void crossProduct(float A[], float B[], float C[]) {
    C[0] = A[1] * B[2] - A[2] * B[1];
    C[1] = -(A[0] * B[2] - A[2] * B[0]);
    C[2] = A[0] * B[1] - A[1] * B[0];
}

void multiply(std::array<std::array<double,3>,3> &mul, double m1[][3], double m2[][3]){
    for (int i = 0; i < 3; i++) {
        for (int  j = 0;j < 3;j++) {
            mul[i][j] = 0;
            std::cout<<"( ";
            for (int  k = 0;k < 3;k++) {
                mul[i][j] += m1[i][k] * m2[k][j];
                std::cout<<m2[i][k]<<" * "<<m1[k][j]<<" = "<<mul[i][j]<<", ";
            }
            std::cout<<" )";

        }

    }
    std::cout<<std::endl;

}

int main(){
    std::array<std::array<float,2>,2> x{{{1,2},{3,4}}};

    //xforms currXform(x);

    //std::stack<xforms> y;
    std::stack<std::array<std::array<float,2>,2>> y;

    y.push(x);
    std::array<std::array<float,4>,4> z;

  std::copy(&y.top()[0][0], &y.top()[0][0] + 2*2, &z[0][0]);

 //      std::cout<<&y.top();
       std::cout<<z[0][0];

    double m11[3][3] = {{1,0,1},
                                               {2,3,4},
                                                {1,2,0}};

    double m22[3][3] = {{2,0,0},
                       {1,1,4},
                       {3,1,0}};

    std::array<std::array<double,3>,3> mul;

multiply(mul, m11, m22);

    for (int i = 0; i < 3; i++) {
        for (
               int j = 0;
                j < 3;
                j++) {
    std::cout<<mul[i][j]<<" ";
        }
std::cout<<std::endl;
    }
float a[3] = {1,2,3};
    float b[3] = {3,0,4};
    float c[3];
crossProduct(a,b,c);

std::cout<<c[0]<<" "<<c[1]<<" "<<c[2];
    return 0;


}