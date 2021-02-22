#include<iostream>
#include <fstream>
#include<cstring>
//#include "rd_direct.h"
#include "rd_display.h"
//#include "rd_enginebase.h"
//#include "rd_direct.h"
#include "pnm_display.h"
#include "rd_error.h"


using std::ofstream;
using std::ios;
float* Image;

//int display_xSize = 200;
//int display_ySize = 200;

//char display_name[30] = "Test";

int frameNumber;
int totalColors = 3;

float backgroundColor[3] = {0.0, 0.0, 0.0};

int pnm_init_display(void){
    //allocate global memory for image
    const int const_display_ySize = display_ySize;
    const int const_display_xSize = display_xSize;
    const int totalColors = 3;

    //allocate memmory for an image
    Image = new float[const_display_ySize*const_display_xSize*totalColors];

    std::cout<<std::endl<<"PNM image size: "<<const_display_ySize*const_display_xSize*totalColors;

return(RD_OK);
}

int pnm_end_display(void){
    // Delete the dynamically allocated image here

    delete[] Image;

    return(RD_OK);
}

int pnm_init_frame(int frame_no) {
    frameNumber = frame_no;


    for (int y = 0; y < display_ySize; y++) {
        for (int x = 0; x < display_xSize; x++) {
            //pnm_write_pixel(x,y,)
            //*(Image+y*display_xSize*totalColors + x*totalColors))*255.0<<" ";
            *(Image + y * display_xSize * totalColors + x * totalColors) = backgroundColor[0]; // Red
            *(Image + y * display_xSize * totalColors + x * totalColors + 1) = backgroundColor[1]; // Green
            *(Image + y * display_xSize * totalColors + x * totalColors + 2) = backgroundColor[2]; // Blue
        }
    }
    return RD_OK;
}

int pnm_end_frame(void){
    // Most involved routine copy contents to a file
    int totalColors =3;
    // FileName is inititalized here, following the convention
   // char fileName[30] = "testing.ppm";

    // declare outstream
    ofstream outStream;

    // First copy everything into the image.
    // pnm_write will read contents from [somewhere]
    // And copy them into the image

    // outstream to file
    outStream.open("testing.ppm", ios::binary);

    // Print header of file
     outStream << "P6\n" << display_xSize << " " << display_ySize << "\n255\n";

std::cout<<"Beginning to write";
    for (int y = 0; y < display_ySize; y++)
    {
        for(int x = 0; x < display_xSize; x++)
        {
            //pnm_write_pixel(x,y,)
            //std::cout<<float(*(Image+y*display_xSize*totalColors + x*totalColors))*255.0<<" ";
          //  std::cout<<int(*(Image+y*display_xSize*totalColors + x*totalColors +1)*255)<<" ";
            outStream.put(int(*(Image+y*display_xSize*totalColors + x*totalColors)*255)); // Red
            outStream.put(int(*(Image+ y*display_xSize*totalColors + x*totalColors + 1)*255)); // Green
            outStream.put(int(*(Image+ y*display_xSize*totalColors + x*totalColors + 2)*255)); // Blue
          //  break;
        }
       // break;
    }

    outStream.close();

    return(RD_OK);
}


int pnm_write_pixel(int x, int y, const float rgb []){
    //std::cout<<"pnm write"<<" r "<<rgb[0]<<" g  "<<rgb[1]<<" b "<<rgb[2]<<" x "<<x<<" y"<<y<<std::endl;
    *(Image + y * display_xSize * totalColors + x * totalColors + 0) = rgb[0];
    *(Image + y * display_xSize * totalColors + x * totalColors + 1) = rgb[1];
    *(Image + y * display_xSize * totalColors + x * totalColors + 2) = rgb[2];


    return(RD_OK);
}

int pnm_read_pixel(int x, int y, float rgb []){
  //  std::cout<<" read pixel is called";
    rgb[0] = *(Image+ y*display_xSize*totalColors + x*totalColors + 0);
    rgb[1] = *(Image+ y*display_xSize*totalColors + x*totalColors + 1);
    rgb[2] = *(Image+ y*display_xSize*totalColors + x*totalColors + 2);
    return(RD_OK);
}


int pnm_set_background(const float rgb []){
    backgroundColor[0] = rgb[0];
    backgroundColor[1] = rgb[1];
    backgroundColor[2] = rgb[2];
    return(RD_OK);
}

int pnm_clear(void){

    for (int y = 0; y < display_ySize; y++)
    {
        for(int x = 0; x < display_xSize; x++)
        {
            //pnm_write_pixel(x,y,)
            //*(Image+y*display_xSize*totalColors + x*totalColors))*255.0<<" ";
            *(Image+y*display_xSize*totalColors + x*totalColors) = backgroundColor[0]; // Red
            *(Image+ y*display_xSize*totalColors + x*totalColors + 1) = backgroundColor[1]; // Green
            *(Image+ y*display_xSize*totalColors + x*totalColors + 2) = backgroundColor[2]; // Blue
        }
    }

    return(RD_OK);
}
