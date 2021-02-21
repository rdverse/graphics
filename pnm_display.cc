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
//    try {
//        for (int y = 0; y < const_display_ySize; y++)
//            for (int x = 0; x < const_display_xSize; x++)
//                for (int c = 0; c < totalColors; c++)
//                    *(Image +
//                    y*const_display_xSize*totalColors +
//                    x*totalColors + c) = 1.0;
//        for (int i = 0; i < const_display_ySize*const_display_xSize*totalColors; i++)
//            *(Image + i) = 1.0;
//    std::fill_n(&Image[0][0][0], display_ySize*display_xSize*3,0);
//
//std::cout<<"pnm display";
//}
//catch(std::exception &e){
//    std::cerr<<"Image could not be initialized"<<e.what();
//}

return(RD_OK);
}

int pnm_end_display(void){
    // Delete the dynamically allocated image here

    delete[] Image;

//    catch(std::exception &e){
//        std::cerr<<"could not delete image array"<<e.what();
//    }
    return(RD_OK);
}

int pnm_init_frame(int frame_no) {
    frameNumber = frame_no;

//      std::fill_n(&Image[0][0][0], display_ySize*display_xSize*3,0);
//    for (int i = 0; i < display_ySize * display_xSize * 3; i++) {
//    *(Image + i) = 0.5;
//}

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

    //catch(std::exception &e){
    //    std::cerr<<"Image could not be re-initialized"<<e.what();
   // }

    return(RD_OK);}

//int pnm_end_frame(void){
//    // Most involved routine copy contents to a file
//
//
//    int totalColors =3;
//    char fileName[30] = "1.ppm";
//
//    //fileName = "1.ppm";
//
//    ofstream outStream;
//
//    outStream.open(fileName, ios::binary);
//
//    // Print header
//    outStream<<display_name<<"\n"<< display_xSize<<"X"<< display_ySize;
////                    *(Image +
////                    y*const_display_xSize*totalColors +
////                    x*totalColors + totalColors) = 1.0;
//
//    for (int y = 0; y < display_ySize-2; y++)
//    {
//        for(int x = 0; x < display_xSize-2; x++)
//        {
//            std::cout<<*(Image+y*display_xSize*totalColors + x*totalColors)<<" ";
//            outStream.put(int(*(Image+y*display_xSize*totalColors + x*totalColors)*255)); // Red
//            outStream.put(int(*(Image+ y*display_xSize*totalColors + x*totalColors + 1)*255)); // Green
//            outStream.put(int(*(Image+ y*display_xSize*totalColors + x*totalColors + 2)*255)); // Blue
//        }
//    }
//
//    outStream.close();
//
//    return(RD_OK);
//}


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
    //outStream<<display_name<<"\n"<< display_xSize<<"X"<< display_ySize;
     outStream << "P6\n" << display_xSize << " " << display_ySize << "\n255\n";

    //                    *(Image +
//                    y*const_display_xSize*totalColors +
//                    x*totalColors + totalColors) = 1.0;
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

//    const int XSIZE = 400;
//    const int YSIZE = 400;
//
//    ofstream out;
//
//    out.open("tests.ppm", ios::binary);
//
//    // Print header
//
//   // out << "P6\n" << XSIZE << " " << YSIZE << "\n255\n";
//
//    for (int y = 0; y < YSIZE; y++)
//    {
//        for(int x = 0; x < XSIZE; x++)
//        {
//            std::cout<<int(((float)x/XSIZE)*255)<<" ";
//            out.put(int(((float)x/XSIZE)*255)); // Red
//            out.put(int(((float)y/YSIZE)*255)); // Green
//            out.put(0.4); // Blue
//        }
//    }
//
//    out.close();
    return(RD_OK);
}






int pnm_write_pixel(int x, int y, const float rgb []){
    //std::cout<<"pnm write"<<" r "<<rgb[0]<<" g  "<<rgb[1]<<" b "<<rgb[2]<<" x "<<x<<" y"<<y<<std::endl;
    *(Image + y * display_xSize * totalColors + x * totalColors + 0) = rgb[0];
    *(Image + y * display_xSize * totalColors + x * totalColors + 1) = rgb[1];
    *(Image + y * display_xSize * totalColors + x * totalColors + 2) = rgb[2];

//    for(int y=0; y<display_ySize; y++) {
//        for (int x = 0; x < display_xSize; x++) {
//            *(Image + y * display_xSize * totalColors + x * totalColors + 0) = rgb[0];
//            *(Image + y * display_xSize * totalColors + x * totalColors + 1) = rgb[1];
//            *(Image + y * display_xSize * totalColors + x * totalColors + 2) = rgb[2];
//        }
//    }
//    Image[y][x][0] = rgb[0];
//    Image[y][x][1] = rgb[1];
//    Image[y][x][2] = rgb[2];
    return(RD_OK);
}

int pnm_read_pixel(int x, int y, float rgb []){
  //  std::cout<<" read pixel is called";
    rgb[0] = *(Image+ y*display_xSize*totalColors + x*totalColors + 0);
    rgb[1] = *(Image+ y*display_xSize*totalColors + x*totalColors + 1);
    rgb[2] = *(Image+ y*display_xSize*totalColors + x*totalColors + 2);

//    rgb[0] = Image[y][x][0];
//    rgb[1] = Image[y][x][1] ;
//    rgb[2] = Image[y][x][2];


    return(RD_OK);
}


int pnm_set_background(const float rgb []){
    backgroundColor[0] = rgb[0];
    backgroundColor[1] = rgb[1];
    backgroundColor[2] = rgb[2];
    return(RD_OK);
}

int pnm_clear(void){
//     for(int y=0; y< display_ySize; y++){
//     for(int x=0; y< display_xSize; x++){
//         Image[y][x][0] = backgroundColor[0];
//         Image[y][x][1] = backgroundColor[1];
//         Image[y][x][2] = backgroundColor[2];
//     }
// }
        //set background color to pnm
//        for (int i = 0; i < display_ySize*display_xSize*3; i++) {
//            *(Image + i) = 0.0;
//        }
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