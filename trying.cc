#include <iostream>
#include "rd_error.h"

using namespace std;

int main () {
    int a = 10;
   int *p;
    //p[0] = {a};
    std::cerr<<RD_INPUT_BAD_BSPLINE_DEGREE;

    int image[10][20][3];
    std::fill_n(&image[0][0][0], 10*20*3,6 );
    //image[][][]=5;
    cout<<image[5][2][1];

    auto image2 = new int[10][20][2];
    image2[1][2][0] = 5;
    cout<<image2[1][2][0];
    delete[] image2;
    cout<<image2[1][2][0];

    //delete[] image;
//
//    try
//    {
////p = &a;S
//        std::cout<<"try"<<p[1000];
//    }
//    catch (std::exception& e)
//    {
////        cout << "An exception occurred. Exception Nr. " << e << '\n';
//        std::cerr<<e.what();
//
//    }
//
    return 0;
}