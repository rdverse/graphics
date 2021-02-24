#include<iostream>
#include <fstream>
#include<cstring>
#include "rd_display.h"
#include "pnm_display.h"
#include "rd_error.h"


using std::ofstream;
using std::ios;
using std::to_string;

float* Image;

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

    // background color is put in the image
    for (int y = 0; y < display_ySize; y++) {
        for (int x = 0; x < display_xSize; x++) {
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
   string fileName = display_name;
   fileName.append("_");
   fileName.append(to_string(frameNumber));
   fileName.append(".ppm");

    // declare outstream
    ofstream outStream;

    // First copy everything into the image.
    // pnm_write will read contents
    // And copy them into the image

    // outstream to file
    outStream.open(fileName, ios::binary);

    // Print header of file
     outStream << "P6\n" << display_xSize << " " << display_ySize << "\n255\n";

//std::cout<<"Beginning to write";
    for (int y = 0; y < display_ySize; y++)
    {
        for(int x = 0; x < display_xSize; x++)
        {
            outStream.put(int(*(Image+y*display_xSize*totalColors + x*totalColors)*255)); // Red
            outStream.put(int(*(Image+ y*display_xSize*totalColors + x*totalColors + 1)*255)); // Green
            outStream.put(int(*(Image+ y*display_xSize*totalColors + x*totalColors + 2)*255)); // Blue
        }
    }
    outStream.close();
    return(RD_OK);
}

// write a pixel value into image
int pnm_write_pixel(int x, int y, const float rgb []){
    *(Image + y * display_xSize * totalColors + x * totalColors + 0) = rgb[0];
    *(Image + y * display_xSize * totalColors + x * totalColors + 1) = rgb[1];
    *(Image + y * display_xSize * totalColors + x * totalColors + 2) = rgb[2];
    return(RD_OK);
}

// read the color for a given pixel
int pnm_read_pixel(int x, int y, float rgb []){
 //   std::cout<<rgb[0]<<" ";

    rgb[0] = *(Image+ y*display_xSize*totalColors + x*totalColors + 0);
    rgb[1] = *(Image+ y*display_xSize*totalColors + x*totalColors + 1);
    rgb[2] = *(Image+ y*display_xSize*totalColors + x*totalColors + 2);
    return(RD_OK);
}

// set the background color
int pnm_set_background(const float rgb []){
    backgroundColor[0] = rgb[0];
    backgroundColor[1] = rgb[1];
    backgroundColor[2] = rgb[2];
    return(RD_OK);
}

// set image back to background
int pnm_clear(void){

    for (int y = 0; y < display_ySize; y++)
    {
        for(int x = 0; x < display_xSize; x++)
        {
            *(Image+y*display_xSize*totalColors + x*totalColors) = backgroundColor[0]; // Red
            *(Image+ y*display_xSize*totalColors + x*totalColors + 1) = backgroundColor[1]; // Green
            *(Image+ y*display_xSize*totalColors + x*totalColors + 2) = backgroundColor[2]; // Blue
        }
    }

    return(RD_OK);
}
