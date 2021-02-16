#include<iostream>
#include <fstream>
#include<cstring>
//#include "rd_direct.h"
//#include "rd_display.h"
//#include "rd_enginebase.h"
//#include "rd_direct.h"
#include "pnm_display.h"
#include "rd_error.h"


using std::ofstream;
using std::ios;
float* Image;

int disp_xSize = 200;
int disp_ySize = 200;

char disp_name[30] = "Test";

int frameNumber;
int totalColors = 3;

const float* backgroundColor;

int pnm_init_display(void){
    //allocate global memory for image
    const int const_disp_ySize = disp_ySize;
    const int const_disp_xSize = disp_xSize;
    const int totalColors = 3;

    //allocate memmory for an image
    Image = new float[const_disp_ySize*const_disp_xSize*totalColors];

    try {
//        for (int y = 0; y < const_disp_ySize; y++)
//            for (int x = 0; x < const_disp_xSize; x++)
//                for (int c = 0; c < totalColors; c++)
//                    *(Image +
//                    y*const_disp_xSize*totalColors +
//                    x*totalColors + c) = 1.0;
//        for (int i = 0; i < const_disp_ySize*const_disp_xSize*totalColors; i++)
//            *(Image + i) = 1.0;

//    std::fill_n(&Image[0][0][0], disp_ySize*disp_xSize*3,0);
std::cout<<"pnm display";
}
catch(std::exception &e){
    std::cerr<<"Image could not be initialized"<<e.what();
}

return(RD_OK);
}

int pnm_end_display(void){
    // Delete the dynamically allocated image here
try{
    delete[] Image;
}
    catch(std::exception &e){
        std::cerr<<"could not delete image array"<<e.what();
    }
    return(RD_OK);
}

int pnm_init_frame(int frame_no){
    frameNumber = frame_no;
    try {
//      std::fill_n(&Image[0][0][0], disp_ySize*disp_xSize*3,0);
        for (int i = 0; i <disp_ySize*disp_xSize*3; i++)
            *(Image + i) = 0.2;
    }
    catch(std::exception &e){
        std::cerr<<"Image could not be re-initialized"<<e.what();
    }

    return(RD_OK);}

int pnm_end_frame(void){
    // Most involved routine copy contents to a file
    int totalColors =3;
    char fileName[30] = "1.ppm";
    //fileName = "1.ppm";

    ofstream outStream;

    outStream.open(fileName, ios::binary);

    // Print header
    outStream<<disp_name<<"\n"<< disp_xSize<<"X"<< disp_ySize;
//                    *(Image +
//                    y*const_disp_xSize*totalColors +
//                    x*totalColors + totalColors) = 1.0;

    for (int y = 0; y < disp_ySize-2; y++)
    {
        for(int x = 0; x < disp_xSize-2; x++)
        {
            std::cout<<disp_xSize<<std::endl<<disp_ySize;//*(Image+y*disp_xSize*totalColors + x*totalColors);
            outStream.put(int(*(Image+y*disp_xSize*totalColors + x*totalColors)*255)); // Red
            outStream.put(int(*(Image+ y*disp_xSize*totalColors + x*totalColors + 1)*255)); // Green
            outStream.put(int(*(Image+ y*disp_xSize*totalColors + x*totalColors + 2)*255)); // Blue
        }
    }

    outStream.close();

    return(RD_OK);
}






int pnm_write_pixel(int x, int y, const float rgb []){
    *(Image+ y*disp_xSize*totalColors + x*totalColors + 0) = rgb[0];
    *(Image+ y*disp_xSize*totalColors + x*totalColors + 1) = rgb[1];
    *(Image+ y*disp_xSize*totalColors + x*totalColors + 2) = rgb[2];
//    Image[y][x][0] = rgb[0];
//    Image[y][x][1] = rgb[1];
//    Image[y][x][2] = rgb[2];
    return(RD_OK);
}

int pnm_read_pixel(int x, int y, float rgb []){

//    rgb[0] = *(Image+ y*disp_xSize*totalColors + x*totalColors + 0);
//    rgb[1] = *(Image+ y*disp_xSize*totalColors + x*totalColors + 1);
//    rgb[2] = *(Image+ y*disp_xSize*totalColors + x*totalColors + 2);

    //    rgb[0] = Image[y][x][0];
//    rgb[1] = Image[y][x][1] ;
//    rgb[2] = Image[y][x][2];
    return(RD_OK);
}


int pnm_set_background(const float rgb []){
    backgroundColor = rgb;
    return(RD_OK);
}

int pnm_clear(void){
//     for(int y=0; y< disp_ySize; y++){
//     for(int x=0; y< disp_xSize; x++){
//         Image[y][x][0] = backgroundColor[0];
//         Image[y][x][1] = backgroundColor[1];
//         Image[y][x][2] = backgroundColor[2];
//     }
// }

        for (int i = 0; i < disp_ySize*disp_xSize*3; i++) {
            *(Image + i) = 1.0;
        }

    return(RD_OK);
}


//#include "pnm_display.h"
//int pnm_init_display(void){
//    return(1);}
//
//int pnm_end_display(void){
//    return(1);}
//
//int pnm_init_frame(int){
//    return(1);}
//
//int pnm_end_frame(void){
//    return(1);}
//
//int pnm_write_pixel(int x, int y, const float rgb []){return(1);}
//
//int pnm_read_pixel(int x, int y, float rgb []){return(1);}
//
//
//int pnm_set_background(const float rgb []){return(1);}
//
//int pnm_clear(void){return(1);}