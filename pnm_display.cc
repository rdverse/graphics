#include "pnm_display.h"
#include "rd_display.h"
#include "rd_error.h"
#include "iostream"
using std::cout;
//extern int *image;
//int image[display_ySize][display_xSize][3];
int pnm_init_display(void){
  //int  image101;
  //image = new int[40];
  cout<<"pnm_init_display";
  cout<<display_xSize;
//  const int xs = (const) display_xSize;
//  const int ys = (const) display_ySize;
//timegm image;
//cout<<image;
    return(RD_OK);
}

int pnm_end_display(void){
    return(RD_OK);}

int pnm_init_frame(int){

    return(RD_OK);}

int pnm_end_frame(void){
    return(RD_OK);}

int pnm_write_pixel(int x, int y, const float rgb []){

    return(RD_OK);
}

int pnm_read_pixel(int x, int y, float rgb []){
    return(RD_OK);
}


int pnm_set_background(const float rgb []){
    return(RD_OK);}

int pnm_clear(void){
    return(RD_OK);
}

