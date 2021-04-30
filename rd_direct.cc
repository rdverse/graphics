//added
#include<iostream>
#include "rd_direct.h"
#include "rd_error.h"
#include "rd_display.h"
#include<math.h>
#include<cmath>
#include <string>
#include<array>
#include<stack>

using std::string;
using std::swap;

// global variable to store frame_no
int frame_number;

// global colors
float DrawColor[] = {1.0, 1.0, 1.0};
float BackgroundColor[] = {0.0 ,  0.0 , 0.0};

//global line points
float lineHprev[4];
float lineHcurr[4];

// Global xforms
std::array<std::array<double,4>,4> currentXform;
//std::array<std::array<std::array<double,4>,4>,20>
double xforms[10][4][4];
int xformIndex = 0;


std::array<std::array<double,4>,4> o2w;
std::array<std::array<double,4>,4> w2c;
std::array<std::array<double,4>,4> c2c;
std::array<std::array<double,4>,4> c2d;

//std::stack<std::array<std::array<double,4>,4>> xforms;
// float* depthBuffer;
//std::array<std::array<float,display_xSize>,display_ySize> depthBuffer;
float* depthBuffer;
// instead of stack use an array here

//global vectors
//we have
float E[3] = {0,0,0};
float At[3] = {0,0,-1};
float Up[3] = {0,1,0};
float FOV = 90;
float Znear = 1.0;
float Zfar = 1000000000;

// we dont have
float U[3];
float V[3];
float A[3];

//for approximated stuff
float NSEG = 21;
////////////////////Transformation stack help////////////////

void REDirect::pointh(float homo[], const float cartesian[3]){
//
//    std::cout<<"w2c matrix"<<std::endl;
//    for(int i = 0; i<4;i++){
//        for(int j = 0; j<4;j++){
//            std::cout<<w2c[i][j]<<" ";
//        }
//        std::cout<<std::endl;
//    }
//
//    std::cout<<"c2c matrix"<<std::endl;
//    for(int i = 0; i<4;i++){
//        for(int j = 0; j<4;j++){
//            std::cout<<c2c[i][j]<<" ";
//        }
//        std::cout<<std::endl;
//    }
    std::copy(&cartesian[0], &cartesian[0] + 4, &homo[0]);
    homo[3] = 1;
}

void REDirect::multiply(std::array<std::array<double,4>,4> &mul, std::array<std::array<double,4>,4> m1, std::array<std::array<double,4>,4> m2){
    for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int  j = 0;j < 4;j++) {
            mul[i][j] = 0;
            for (unsigned int  k = 0;k < 4;k++) {
                mul[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void REDirect::multiply(float transp[], float pointHomo[], std::array<std::array<double,4>,4> transform){

    for (unsigned int i = 0; i < 4; i++) {
        transp[i] = 0;
        for (unsigned int  j = 0;j < 4;j++) {
                transp[i] += transform[i][j] * pointHomo[j];
        }
    }
}

void REDirect::crossProduct(float C[], float A[], float B[]) {
    C[0] = ((A[1] * B[2]) - (A[2] * B[1]));
    C[1] = ((A[2] * B[0]) - (A[0] * B[2]));
    C[2] = ((A[0] * B[1]) - (A[1] * B[0]));
}

void REDirect::normalize_vector(float vect[]){
    float vectNorm = sqrt(pow(vect[0], 2) + pow(vect[1], 2) + pow(vect[2], 2));
    vect[0] = vect[0]/vectNorm;
    vect[1] = vect[1]/vectNorm;
    vect[2] = vect[2]/vectNorm;
}

void REDirect::calc_w2c_params(void){
    // A = At- E
    A[0] = At[0] - E[0];
    A[1] = At[1] - E[1];
    A[2] = At[2] - E[2];
    // Normalize A
    normalize_vector(A);
    // V = AXUp
    crossProduct( V,A, Up);
    // Normalize V
    normalize_vector(V);
    // U = VXA
    crossProduct(U,V, A);

 //   std::cout<<std::endl<<"V : "<<V[0]<<" "<<V[1]<<" "<<V[2]<<std::endl;
 //   std::cout<<std::endl<<"U : "<<U[0]<<" "<<U[1]<<" "<<U[2]<<std::endl;
 //   std::cout<<std::endl<<"A : "<<A[0]<<" "<<A[1]<<" "<<A[2]<<std::endl;
}


void REDirect::print_matrix(string stringp, std::array<std::array<double,4>,4> transform ){
  //  std::cout<<std::endl<<stringp<<std::endl;
    for(int i = 0; i<4;i++){
        for(int j = 0; j<4;j++){
            std::cout<<transform[i][j]<<" ";
        }
   //     std::cout<<std::endl;
    }
//std::cout<<std::endl;

}
//////////////////////Transformation stack////////////////////////
            //////////World to Camera////////////
 void REDirect::world_to_camera(void){

     calc_w2c_params();
   // Using the given eye point, look at point and up vector,
   // all expressed in world coordinates, returns the transformation from world to camera coordinates.

    std::array<std::array<double,4>,4> mat1 = {{{V[0],V[1],V[2],0},
                                                {U[0],U[1],U[2],0},
                                                {A[0],A[1],A[2],0},
                                                {0   ,0   ,0   ,1}}};

    std::array<std::array<double,4>,4> mat2 = {{{1,0,0,-E[0]},
                                                {0,1,0,-E[1]},
                                                {0,0,1,-E[2]},
                                                {0,0,0,   1}}};

multiply(w2c, mat1, mat2);

}

//////////Camera to clip////////////
void REDirect::camera_to_clip(void){

    float tant2 =  tan((FOV/(2*180.0))*M_PI);
    float a = (float)display_xSize/(float)display_ySize;

    c2c = {{{ (1/(2*a*tant2)),0,0.5,0},
           {0,(1/(2*tant2)),0.5,0},
           {0,0,(Zfar/(Zfar-Znear)),-((Zfar*Znear)/(Zfar-Znear))},
           {0   ,0   ,1 ,0}}};


}


             /////Clip to device/////
 void REDirect::clip_to_device(void){


    // Create the clip to device matrix here
    //
//                 calc_w2c_params();
//                 // Using the given eye point, look at point and up vector,
//                 // all expressed in world coordinates, returns the transformation from world to camera coordinates.
//
                 c2d = {{{(double)display_xSize,0,0,0},
                        {0, -(double)display_ySize,0,(double)display_ySize},
                        {0,0,1,0},
                        {0   ,0   ,0,1}}};
//
//                 std::array<std::array<double,4>,4> mat2 = {{{1,0,0,-E[0]},
//                                                                    {0,1,0,-E[1]},
//                                                                    {0,0,1,-E[2]},
//                                                                    {0,0,0,   1}}};
//
//                 multiply(w2c, mat1, mat2);

}




/////////////////////Main stuff///////////////////////////////////////////
int REDirect::rd_display(const string & name, const string & type, const string & mode)
{
    // Nothing to implement in this function, everthing is done behind the scenes
    return RD_OK;
}

int REDirect::rd_format(int xresolution, int yresolution)
{

    // store values of resolution in global variables. This is required in pnm
    // but we already have display_xSize and display_ySize
   //  std::cout<<xresolution<<yresolution;
    return RD_OK;
}


int REDirect::rd_frame_begin(int frame_no)
{
    // Store the frame value in a global variable
   // rd_disp_init_frame(frame_number);
    frame_number = frame_no;
   // DrawColor[3] = {0.0, 0.0, 0.0};
   // BackgroundColor[3] = {1.0 ,  1.0 , 1.0};
    //Calling world begin or init frame will give error
    return RD_OK;
}

int REDirect::rd_world_begin(void) {
  // initialize depth buffer
    depthBuffer = new float[display_ySize*display_xSize];

    for( int i = 0; i < display_ySize; i++) {
        for ( int j = 0; j < display_xSize; j++) {
           // std::cout<<display_xSize*(j-1) +i<<" ";
            *(depthBuffer + display_xSize*i + j) = 1;
            //depthBuffer[i][j] = 1;

        }
   //     std::cout<<std::endl;
    }
    //initialize display for new image, use below function
    // float testreturn[3] = {0,0,0};
    // check_write_pixel(10,10, testreturn);
    //rd_print_error(RD_OK, "s01.rd");
//
    // Set the initial xform as an identity matrix
    for(unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < 4; j++) {
            if(i==j)
            {
                currentXform[i][j] = 1;
            }
            else{
                currentXform[i][j] = 0;
            }
        }
    }
    //The world to camera transformation can be computed using the camera eyepoint, look at point and up vector.
    world_to_camera();
    //The camera to clipping coordinate transformation matrix can be computed using the near and far clipping depths and the field of view.
    camera_to_clip();
    //These last two transformations can be combined and stored as the world to clipping coordinate matrix.

    //////////////////////// Next thing to figure out ///////////////////////////
    //The clipping coordinate to device coordinate transform is also computed here.
    clip_to_device();


    try {
        return (rd_disp_init_frame(frame_number));
    }
    catch (std::exception &e) {
        std::cerr << RD_INPUT_DISPLAY_INITIALIZATION_ERROR;
        return (RD_INPUT_DISPLAY_INITIALIZATION_ERROR);
    }
}

int REDirect::rd_world_end(void)
    {
   // Finish off the display
        try {
            return (rd_disp_end_frame());
        }
        catch (std::exception &e) {
            std::cerr << RD_INPUT_UNINITIALIZED_DISPLAY;
            return (RD_INPUT_UNINITIALIZED_DISPLAY);
        }
   // just end frame, dont end display here, giving error
}


int REDirect::rd_frame_end(void)
{
 //   same as rd_world_end, have one call the other
    return RD_OK;
}


/**********************   Camera  ******************************************/

int REDirect::rd_camera_eye(const float eyepoint[3]){
    E[0] = eyepoint[0];
    E[1] = eyepoint[1];
    E[2] = eyepoint[2];
    // Store the values passed in into the global variable(s) set aside for this purpose.
    return(RD_OK);
}
int REDirect::rd_camera_at(const float atpoint[3]) {

//    Store in global variables.
    At[0] = atpoint[0];
    At[1] = atpoint[1];
    At[2] = atpoint[2];
    return(RD_OK);
}

int REDirect::rd_camera_up(const float up[3]){
    // Store globally.
    Up[0] = up[0];
    Up[1] = up[1];
    Up[2] = up[2];
    return(RD_OK);

}
int REDirect::rd_camera_fov(float fov) {
    // Store globally.
    FOV = fov;
    return(RD_OK);
}
int REDirect::rd_clipping(float znear, float zfar) {
    // Store the values in the near and far global clipping depths respectively.
     Znear = znear;
     Zfar = zfar;
    return(RD_OK);
}

/**********************   Transformations **********************************/

int REDirect::rd_translate(const float offset[3]){
   // std::cout<<offset[0]<<" "<<offset[1]<<" "<<offset[2];
    // Takes an array of three floats, creates a translation matrix and multiplies it by the current transform, storing the result back in the current transform.
    std::array<std::array<double,4>,4> translateMatrix = {{{1,0,0,offset[0]},
                                                                  {0,1,0,offset[1]},
                                                                  {0,0,1,offset[2]},
                                                                  {0,0,0,1}}};
    std::array<std::array<double,4>,4> tempCur;

    std::copy(&currentXform[0][0], &currentXform[0][0] + 4*4, &tempCur[0][0]);

    multiply(currentXform, tempCur, translateMatrix);

    return(RD_OK);
}

int REDirect::rd_scale(const float scale_factor[3]){
    // Takes an array of three floats, the scale factors in x, y, and z, creates a scale matrix and multiplies it by the current transform,
    // storing the result back in the current transform.
    std::array<std::array<double,4>,4> scaleMatrix = {{{scale_factor[0],0,0,0},
                                                                  {0,scale_factor[1],0,0},
                                                                  {0,0,scale_factor[2],0},
                                                                  {0,0,0,1}}};
    std::array<std::array<double,4>,4> tempCur;
    std::copy(&currentXform[0][0], &currentXform[0][0] + 4*4, &tempCur[0][0]);
    multiply(currentXform, tempCur, scaleMatrix);
    return(RD_OK);
}

int REDirect::rd_rotate_xy(float angle){
    // Takes a float which is the angle of rotation in degrees and creates a rotation matrix in the xy plane.
    // The matrix is multiplied by the current transformation matrix and the results stored back in the current transform.
    float  theta = (angle/180)*M_PI;

    std::array<std::array<double,4>,4> xyMatrix = {{{cos(theta),  -sin(theta),0,0},
                                                      {sin(theta),cos(theta),0,0},
                                                      {0,         0,         1,0},
                                                      {0,         0,         0,1}}};

    std::array<std::array<double,4>,4> tempCur;
    std::copy(&currentXform[0][0], &currentXform[0][0] + 4*4, &tempCur[0][0]);
    multiply(currentXform, tempCur, xyMatrix);
    return(RD_OK);
}

int REDirect::rd_rotate_yz(float angle){
    //Ditto in the yz plane.
    float theta = (angle/180)*M_PI;

    std::array<std::array<double,4>,4> yzMatrix = {{{1,  0,                  0,   0},
                                                   {0,   cos(theta), -sin(theta),  0},
                                                   {0,   sin(theta), cos(theta),  0},
                                                   {0,            0,          0,  1}}};

    std::array<std::array<double,4>,4> tempCur;
    std::copy(&currentXform[0][0], &currentXform[0][0] + 4*4, &tempCur[0][0]);
    multiply(currentXform, tempCur, yzMatrix);
    return(RD_OK);
}
int REDirect::rd_rotate_zx(float angle){
    // Same here.
    float theta = (angle/180)*M_PI;

    std::array<std::array<double,4>,4> zxMatrix = {{{ cos(theta), 0,       -sin(theta),       0},
                                                   {0,            1,                 0,       0},
                                                   {0,   sin(theta),        cos(theta),       0},
                                                   {0,            0,                 0,       1}}};

    std::array<std::array<double,4>,4> tempCur;
    std::copy(&currentXform[0][0], &currentXform[0][0] + 4*4, &tempCur[0][0]);
    multiply(currentXform, tempCur, zxMatrix);
    return(RD_OK);
}

int REDirect::rd_matrix(const float * mat){
    return(RD_OK);
}
//check
int REDirect::rd_xform_push(void){
  //  xforms.push(currentXform);
    // Push a copy of the current transform onto the transformation stack. The current transformation is left unchanged.
print_matrix("push current", currentXform);
    xformIndex = xformIndex + 1;
    for(unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < 4; j++) {

                xforms[xformIndex][i][j] = currentXform[i][j];

        }
    }

    return(RD_OK);
}
//check
int REDirect::rd_xform_pop(void){
   // std::copy(&xforms.top()[0][0], &xforms.top()[0][0] + 4*4, &currentXform[0][0]);
   // xforms.pop();
    // Set the initial xform as an identity matrix
    //xformIndex = xformIndex-1;

    print_matrix("before pop", currentXform);
    for(unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < 4; j++) {
                currentXform[i][j] = xforms[xformIndex][i][j];

        }
    }

    print_matrix("after pop", currentXform);
    xformIndex =xformIndex-1;
    return(RD_OK);
    // Pop the top of the transformation stack into the current transform.
}

/***********************************************************/

void REDirect::check_write_pixel(int x, int y, float z = 0) {
    // Check if pixel is within bounds
    if(!((x<0)||(x>=display_xSize)||(y<0)||(y>=display_ySize)))
    {
//    if(z < *(depthBuffer + display_xSize*(y-1)+x )){
        if(z < *(depthBuffer + display_xSize*y + x)) {

            rd_write_pixel(int(x), int(y), DrawColor);
            //depthBuffer[y][x] = z;
            *(depthBuffer + display_xSize*y + x) = z;
        }
        }
}


int REDirect::rd_color(const float color[])
{
    // Copy the color contents into global drawColor
    DrawColor[0] = color[0];
    DrawColor[1] = color[1];
    DrawColor[2] = color[2];
    return RD_OK;
}

int REDirect::rd_render_cleanup(void){
 delete[] depthBuffer;
    return(RD_OK);
}


/////////////?MEthods /////////////

 int REDirect::rd_point(const float p[3]){

    // Only have to write the pixel at the given co-ordinates
    // Takes a point, turns it into a homogeneous point and passes it to the point pipeline.
    float ph[4];
    ph[0] = p[0];
    ph[1] = p[1];
     ph[2] = p[2];
     ph[3] = 1;
    point_pipeline(ph);
     return(RD_OK);
}

// store background color in global variable
 int REDirect::rd_background(const float color[]) {
     BackgroundColor[0] = color[0];
     BackgroundColor[1] = color[1];
     BackgroundColor[2] = color[2];
    return (rd_set_background(BackgroundColor));
}


void REDirect::swap_points(float &p1, float &p2){
    float temp = p1;
    p1 = p2;
    p2 = temp;
}


/////////////// Line //////////////////////////

int REDirect::rd_line(const float start[3], const float end[3]){

    bool draw = false;

    // convert point to homogeneous here and then send into line pipeline
  //  std::cout<<"rd line start coordinates :"<<start[0]<<" "<<start[1]<<" "<<start[2]<<std::endl;

    float starth[4];
    float endh[4];
    pointh(starth, start);
    pointh(endh, end);
    starth[3] =1;
    endh[3]=1;
  //  std::cout<<"rd line homogeneousstart coordinates :"<<starth[0]<<" "<<starth[1]<<" "<<starth[2]<<std::endl;

    // set p1
    // draw is false, move only
    line_pipeline(starth, draw);
    draw = true;
    // move and draw line
    line_pipeline(endh, draw);
  //  std::cout<<"complete executing line";

    return(RD_OK);
}


void REDirect::line_pipeline(float lineH[], bool draw = false){

    float lineH1[4];
    float lineH2[4];
    float lineH3[4];


    multiply(lineH1, lineH, currentXform); //o2w
    multiply(lineH2, lineH1, w2c);
    multiply(lineH3, lineH2, c2c);

if(draw){

    std::copy(&lineH3[0], &lineH3[0] + 4, &lineHcurr[0]);
    // line clipping routine here
    line_clipping();

    // make LineHcurr global

    //draw line now. The line should be clipped by now.
}

else{
    std::copy(&lineH3[0], &lineH3[0] + 4, &lineHprev[0]);
}

}


//function to calculate boundary coordinates and boundary kodes
void REDirect::line_b_coord_kode(float Bcoord[], int Bkode[], float lineH[]){

    Bcoord[0] = lineH[0];
    Bcoord[1] = lineH[0] - lineH[3];

    Bcoord[2] = lineH[1];
    Bcoord[3] = lineH[1] - lineH[3];

    Bcoord[4] = lineH[2];
    Bcoord[5] = lineH[2] - lineH[3];

    for(int i=5;i>=0;i--){
        //case negative
        //std::cout<<Bcoord[i]<<std::endl;
        if(Bcoord[i]<0){
            Bkode[i] = 1;
        }
            //case positive
        else{
            Bkode[i] = 0;
        }
    }
}

void REDirect::line_clipping(){

// clip coordinates are stored globally

// This function takes the current and previous coordinates and clips the line

float BcoordCurr[6];
float BcoordPrev[6];

int kodeCurr[6];
int kodePrev[6];


    line_b_coord_kode(BcoordCurr, kodeCurr, lineHcurr);
    line_b_coord_kode(BcoordPrev, kodePrev, lineHprev);

std::cout<<std::endl<<std::endl<<std::endl;
std::cout<<std::endl<<"Testing the initial coordinates"<<std::endl;

std::cout<<lineHcurr[0]<<" "<<lineHcurr[1]<<lineHcurr[2]<<" "<<lineHcurr[3]<<std::endl;
std::cout<<BcoordCurr[0]<<" "<<BcoordCurr[1]<<" "<<BcoordCurr[2]<<" "<<BcoordCurr[3]<<" "<<BcoordCurr[4]<<" "<<BcoordCurr[5]<<std::endl;

std::cout<<kodePrev[0]<<" "<<kodePrev[1]<<" "<<kodePrev[2]<<" "<<kodePrev[3]<<" "<<kodePrev[4]<<" "<<kodePrev[5]<<std::endl;
std::cout<<kodeCurr[0]<<" "<<kodeCurr[1]<<" "<<kodeCurr[2]<<" "<<kodeCurr[3]<<" "<<kodeCurr[4]<<" "<<kodeCurr[5]<<std::endl;
std::cout<<std::endl<<std::endl<<std::endl;


std::stack<int> kodes;

// to store if it is a in to out or out to in
std::stack<int> kodeType;

bool make = true;

for(int i = 0; i<5;i++) {
    int k0 = kodePrev[i];
    int k1 = kodeCurr[i];

    // do only non-trivial stuff
  //  std::cout<<i;
   // std::cout<<k0<<" "<<k1<<std::endl;
    if(k0&k1){
     //   std::cout<<"Do nothing";
    }
    else{
        if(k0|k1){
            if(k0>k1){
                kodeType.push(0);
                kodes.push(i);
            }
            else{
                kodeType.push(1);
                kodes.push(i);
            }
        }
    }
}

///////////alpha calculations here///////////
float amin = 0;
float amax = 1.0;

while(!kodeType.empty()){
    int kodeIndex = kodes.top();
    int kType = kodeType.top();

    kodeType.pop();
    kodes.pop();
    float BC0 = BcoordPrev[kodeIndex];
    float BC1= BcoordCurr[kodeIndex];
    float alpha = BC0/(BC0-BC1);;

    if(kType==0){
        alpha>amin ? amin=alpha : amin= amin;
    } else{
        alpha<amax ? amax=alpha : amax= amax;
    }
}

/////////adjust lines now////////
lineHprev[0] = amin*lineHprev[0];
lineHprev[1] = amin*lineHprev[1];
lineHprev[2] = amin*lineHprev[2];
lineHprev[3] = amin*lineHprev[3];

lineHcurr[0] = amax*lineHcurr[0];
lineHcurr[1] = amax*lineHcurr[1];
lineHcurr[2] = amax*lineHcurr[2];
lineHcurr[3] = amax*lineHcurr[3];

std::cout<<"amin : "<<amin<<" amax : "<<amax<<std::endl;
    if (make) {
        draw_line();
    }
}

//void REDirect::draw_line(float lineHcurr[]){
//
//    float p1[4];
//    float p2[4];
//    float ptemp[4];
//
//    std::copy(&lineHcurr[0], &lineHcurr[0] + 4, &ptemp[0]);
//
//
////    lineHprev[0] = lineHprev[0]/lineHprev[3];
////    lineHprev[1] = lineHprev[1]/lineHprev[3];
////    lineHprev[2] = lineHprev[2]/lineHprev[3];
////    lineHprev[3] = lineHprev[3]/lineHprev[3];
////
////
////    lineHcurr[0] = lineHcurr[0]/lineHcurr[3];
////    lineHcurr[1] = lineHcurr[1]/lineHcurr[3];
////    lineHcurr[2] = lineHcurr[2]/lineHcurr[3];
////    lineHcurr[3] = lineHcurr[3]/lineHcurr[3];
//
//    //convert clip to device coords here
//    multiply(p1, lineHprev, c2d);
//    multiply(p2, lineHcurr, c2d);
//
//    std::copy(&ptemp[0], &ptemp[0] + 4, &lineHprev[0]);
//
////    std::cout<<"after c2d start coordinates :"<<std::endl<<p1[0]<<" "<<p1[1]<<" "<<p1[2]<<" "<<p1[3]<<std::endl;
////    std::cout<<"after c2d end coordinates :"<<std::endl<<p2[0]<<" "<<p2[1]<<" "<<p2[2]<<" "<<p2[3]<<std::endl;
//
////
//    p1[0] = p1[0]/p1[3];
//    p1[1] = p1[1]/p1[3];
//    p1[2] = p1[2]/p1[3];
//    p1[3] = p1[3]/p1[3];
//
//    p2[0] = p2[0]/p2[3];
//    p2[1] = p2[1]/p2[3];
//    p2[2] = p2[2]/p2[3];
//    p2[3] = p2[3]/p2[3];
// //   std::cout<<"after c2d start coordinates :"<<std::endl<<p1[0]<<" "<<p1[1]<<" "<<p1[2]<<std::endl;
////    std::cout<<"after c2d end coordinates :"<<std::endl<<p2[0]<<" "<<p2[1]<<" "<<p2[2]<<std::endl;
//
//    // Read the coordinates of line start point
//    float x0 = p1[0];
//    float y0 = p1[1];
//
//    // Read coordinates of line end point
//    float x1 = p2[0];
//    float y1 = p2[1];
//
// //   std::cout<<"start coordinates :"<<p1[0]<<" "<<p1[1]<<" "<<p1[2];
////    std::cout<<"end coordinates :"<<p2[0]<<" "<<p2[1]<<" "<<p2[2];
//        // Calculate dx (start-end)x
//        float dx = x1 - x0;
//        float dy = y1 - y0;
//
//        //  std::cout<<"dy :"<<dy<<" dx: "<<dx;
//
//        // More horizontal (dx>dy)
//        if (abs(dy)<=abs(dx)){
//            //      std::cout<<"dy<dx";
//            if (dx < 0) {
//                swap(x0, x1);
//                swap(y0, y1);
//            }
//            line_more_horizontal(x0, y0, x1, y1);
//        }
//            //more vertical (dy>dx)
//        else {
//            // if dy<0, swap end points (by reference)
//            if (dy < 0) {
//                //     std::cout<<std::endl<<"y0: "<<y0<<" y1: "<<y1;
//                swap(x0, x1);
//                swap(y0, y1);
//                //       std::cout<<"swap complete";
//            }
////        std::cout<<std::endl<<"y0: "<<y0<<" y1: "<<y1;
//            line_more_vertical(x0, y0, x1, y1);
//        }
//
//}

void REDirect::draw_line(){

    float p1[4];
    float p2[4];
    float ptemp[4];

    std::copy(&lineHcurr[0], &lineHcurr[0] + 4, &ptemp[0]);

    //convert clip to device coords here
    multiply(p1, lineHprev, c2d);
    multiply(p2, lineHcurr, c2d);

    std::copy(&ptemp[0], &ptemp[0] + 4, &lineHprev[0]);

    p1[0] = p1[0]/p1[3];
    p1[1] = p1[1]/p1[3];
    p1[2] = p1[2]/p1[3];
    p1[3] = p1[3]/p1[3];

    p2[0] = p2[0]/p2[3];
    p2[1] = p2[1]/p2[3];
    p2[2] = p2[2]/p2[3];
    p2[3] = p2[3]/p2[3];


    // Read the coordinates of line start point
    float x1 = p1[0];
    float y1 = p1[1];
    float z1 = p1[2];

    // Read coordinates of line end point
    int x2 = p2[0];
    int y2 = p2[1];
    float z2 = p2[2];


    // Calculate dx (end-start)x
    float dx = x2-x1;
    float dy = y2-y1;
    float dz = z2-z1;

    int NSTEPS;

    if(abs(dx)>abs(dy)) {
        NSTEPS = abs(dx);
    }
     else{
         NSTEPS = abs(dy);
     }

    float x = x1;
    float y = y1;
    float z = z1;

    dx = dx/NSTEPS;
    dy = dy/NSTEPS;
    dz = dz/NSTEPS;

   // std::cout<<abs(dx)<<" "<<dx<<" "<<abs(dy)<<" "<<dy<<" ";

    //  std::cout<<z0<<" "<<z1<<std::endl;
    check_write_pixel(int(x), int(y), z);
    for(int i=0;i<NSTEPS;i++){
        x = x + dx;
        y = y + dy;
        z = z + dz;
       // std::cout<<dx<<" ";
        check_write_pixel(int(x), int(y), z);
    }
}

void REDirect::line_more_horizontal(float xs, float ys, float xe, float ye)
{
    // Swapping is done in main line function , dont worry about it
    float x = xs;
    float y = ys;

    float dy = ye - ys;
    float dx = xe - xs;

    float yi = 1;

    if(dy<0){
        yi = -1;
        dy = -dy;
    }
    // p0
    float p = 2*dy - dx;

    while(x<=xe){

        // Draw the first point
        check_write_pixel(int(x), int(y));
        if(p<0){
            //No change in y;
            // Only p changes
            p = p + 2*dy;
        } else if (p>=0){
            // update p
            y = y + yi;
            p = p + (2*dy - 2*dx);

        }
        //In any case increment x
        x++;
    }
}


void REDirect::line_more_vertical(float xs, float ys, float xe, float ye)
{
    // Swapping is done in main line function , dont worry about it
    float x = xs;
    float y = ys;

    float dy = ye - ys;
    float dx = xe - xs;
    
    float xi = 1;

    if(dx<0){
        xi = -1;
        dx = -dx;
    }

    // p0
    float p = 2*dx - dy;

    while(y<=ye){
        // Draw the first point
        check_write_pixel(int(x), int(y));
        if(p<0){
            //No change in y;
            // Only p changes
            p = p + 2*dx;
        } else if (p>=0){
            // update p
            p = p + (2*dx - 2*dy);
            x = x + xi;
        }
        //In any case increment y
        y++;
    }
}


//////////////////// Circle /////////////////////////////

int REDirect::rd_circle(const float center[3], float radius)
{
    float po = 1 - radius;
    int x = 0;
    int y = radius;
    int xp = int(center[0]);
    int yp = int(center[1]);

    float p = po;

    while(y>=x){
        circle_plot_points(x,y,xp,yp);
       // x = x+1;
        if(p<0){
            // try 2x+1 as well
            p = p + 2*x +3;
        }
        else if(p>=0){
            y = y-1;
            p = p + (2*x - 2*y + 3);
        }
        else{
            std::cerr<<RD_INPUT_ILLEGAL_FLAG_VALUE;
        }
        x++;
    }
    return RD_OK;
}

void REDirect::circle_plot_points(int x, int y, int xp, int yp){
// Plot points on 8 octants
    check_write_pixel(xp+x, yp+y);
    check_write_pixel(xp-x, yp+y);
    check_write_pixel(xp+x, yp-y);
    check_write_pixel(xp-x, yp-y);
    check_write_pixel(xp+y, yp+x);
    check_write_pixel(xp-y, yp+x);
    check_write_pixel(xp+y, yp-x);
    check_write_pixel(xp-y, yp-x);
}

////////////////////////Fill /////////////////////////
// Round the color valuesand ceil in nearest integer
double round_up_ceil(double value, int decimal_points = 1) {
    const double multiplier = std::pow(10.0, decimal_points);
    return(std::ceil(value * multiplier) / multiplier);
}

// main fill function
 int REDirect::rd_fill(const float seed_point[3]){
fill_helper(int(seed_point[0]), int(seed_point[1]));
return(RD_OK);
}

void REDirect::fill_helper(int x, int y){

  if(boundary_check(x,y)){
        return;
    }
    float seed_color[3];
    //pass seed color as a reference and get seed color
    rd_read_pixel(x,y,&seed_color[0]);

    // The color read is not exact and has a lot of decimals
    // ceiling the values
    seed_color[0] = round_up_ceil(seed_color[0]);
    seed_color[1] = round_up_ceil(seed_color[1]);
    seed_color[2] = round_up_ceil(seed_color[2]);

 if( ( (seed_color[0]!=BackgroundColor[0]) && (seed_color[1]!=BackgroundColor[1]) && (seed_color[2]!=BackgroundColor[2]) ) ) {
        return;
    }
    check_write_pixel(x, y);

    // Following the name convention of WASD as arrow indications for the four point fill algorithm
    int D[2] = {x+1, y};
    int A[2] = {x-1, y};
    int W[2] = {x, y+1};
    int S[2] = {x, y-1};
// recursive calls
    fill_helper(D[0], D[1]);
    fill_helper(A[0], A[1]);
    fill_helper(W[0], W[1]);
    fill_helper(S[0], S[1]);
}

// check if point is withing the boundary
bool REDirect::boundary_check(int x, int y){
    if((x<0)||(x>=display_xSize)||(y<0)||(y>=display_ySize))
    {
        return(true);
    }
    else{
        return(false);
    }
}


///**********Camera*************************/
//int REDirect::rd_camera_eye(const float eyepoint[3])
//{
//    return RD_OK;
//}
//int REDirect::rd_camera_at(const float atpoint[3])
//{
//    return RD_OK;
//}
//int REDirect::rd_camera_up(const float up[3])
//{
//    return RD_OK;
//}
//int REDirect::rd_camera_fov(float fov)
//{
//    return RD_OK;
//}
//int REDirect::rd_clipping(float znear, float zfar)
//{
//    return RD_OK;
//}
//
////
/////**********************   Transformations **********************************/
//
//int REDirect::rd_translate(const float offset[3])
//
//    return RD_OK;
//}
//
//int REDirect::rd_scale(const float scale_factor[3])
//{
//    return RD_OK;
//}
//
//int REDirect::rd_rotate_xy(float angle)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_rotate_yz(float angle)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_rotate_zx(float angle)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_matrix(const float * mat)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_xform_push(void)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_xform_pop(void)
//{
//    return RD_OK;
//}
////
/////**********************   Geometric Objects  *******************************/
//
//int REDirect::rd_bezier_curve(const string & vertex_type,
//                    int degree, const float * vertex)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_bezier_patch(const string & vertex_type,
//                    int u_degree, int v_degree,
//                    const float * vertex)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_catmull_clark_sds(const string & vertex_type,
//                         float * coord, int nvertex,
//                         int * vertex_list, int nface,
//                         int * crease_list, int ncrease,
//                         float *sharpness)
//{
//    return RD_OK;
//}
//
//
//
//
//
//
//
//
//int REDirect::rd_lineset(const string & vertex_type,
//               int nvertex, const float * vertex,
//               int nseg, const int * seg)
//{
//    return RD_OK;
//}
//
//
////int REDirect::rd_point(const float p[3])
////{
////    return RD_OK;
////}
//
//
void REDirect::point_pipeline(float pH[]){

    float pH1[4];
    float pH2[4];
    float pH3[4];
    float pH4[4];

    // step 1 : object to world transformation
    multiply(pH1, pH, currentXform);

   // std::cout<<pH1[0]<<" "<<pH1[1]<<" "<<pH1[2]<<" "<<pH1[3]<<std::endl;

    multiply(pH2, pH1, w2c);

   // std::cout<<pH2[0]<<" "<<pH2[1]<<" "<<pH2[2]<<" "<<pH2[3]<<std::endl;

    multiply(pH3, pH2, c2c);

   // std::cout<<pH3[0]<<" "<<pH3[1]<<" "<<pH3[2]<<" "<<pH3[3]<<std::endl;
    //convert clip to device coords here
    multiply(pH4, pH3, c2d);

    pH4[0] = pH4[0]/pH4[3];
    pH4[1] = pH4[1]/pH4[3];
    pH4[2] = pH4[2]/pH4[3];
    pH4[3] = pH4[3]/pH4[3];

 //   std::cout<<pH4[0]<<" "<<pH4[1]<<" "<<pH4[2]<<" "<<pH4[3]<<std::endl;

    //rd_write_pixel(int(pH4[0]), int(pH4[1]), DrawColor);
    check_write_pixel(int(pH4[0]), int(pH4[1]), pH[2]);
}


int REDirect::rd_pointset(const string & vertex_type,
                int nvertex, const float * vertex)
{
    for(int i=0;i<nvertex;i++){
        float p[4];
        p[0] = vertex[i*3];
        p[1] = vertex[i*3+1];
        p[2] = vertex[i*3+2];
        p[3] = 1;
        point_pipeline(p);
    }
    return RD_OK;
}

int REDirect::rd_polyset(const string & vertex_type,
                         int nvertex, const float * vertex,
                         int nface,   const int * face)
{
    // this flag tells us if it is the start of the face, in which case, point has to be moved only

    int vertexTracer = 0;
    int faceCount = 0;

    // for the variable
    int startVertex = 0;
    int currVertex = 0;

int faceTraversed=0;
    bool draw = false;

                startVertex = face[vertexTracer];
            currVertex = face[vertexTracer];

    while(true){
        // for each face, draw all points
       // std::cout<<currVertex<<" ";
        float p[4];

        if(faceTraversed==nface){
            break;
        }

        else if(currVertex==-1){
            // draw to the initial point
            draw=true;
            p[0] = vertex[startVertex*3];
            p[1] = vertex[startVertex*3+1];
            p[2] = vertex[startVertex*3+2];
            p[3] = 1;
            line_pipeline(p, draw);

            vertexTracer++;
            currVertex = face[vertexTracer];
            startVertex = currVertex;
            draw=false;
            faceTraversed++;
        }

        else{
            p[0] = vertex[currVertex*3];
            p[1] = vertex[currVertex*3+1];
            p[2] = vertex[currVertex*3+2];
            p[3] = 1;

            line_pipeline(p, draw);
            vertexTracer++;
            currVertex = face[vertexTracer];
            draw=true;
        }
    }
    return RD_OK;
}

//int REDirect::rd_polyset(const string & vertex_type,
//               int nvertex, const float * vertex,
//               int nface,   const int * face)
//{
//    // this flag tells us if it is the start of the face, in which case, point has to be moved only
//    bool faceStart = true;
//    int faceCount = 0;
//
//    for(int i = 0; i< nface;i++){
//        // use i variable to make sure all faces are covered
//
//        // see if a -1 is encountered
//        if(face[i+faceCount]!=-1){
//
//            float p[4];
//            // extract the vertex index from list of faces and then draw the face
//            p[0] = vertex[face[i+faceCount]*3];//x
//            p[1] = vertex[face[i+faceCount]*3+1];//y
//            p[2] = vertex[face[i+faceCount]*3+2];//z
//            p[3] = 1;
//            // start of the face then only move the point
//            if(faceStart){
//                line_pipeline(p, false);
//                }
//            // else draw
//            else{
//                line_pipeline(p, true);
//            }
//            //set the start flag as false
//            faceStart=false;
//        }
//
//        else{
//            //if -1 is encountered faceStart is true.
//            // increment faceCount so that we go to next face in the list
//    faceCount++;
//    faceStart = true;
//    }
//    }
//    return RD_OK;
//}


int REDirect::rd_cone(float height, float radius, float thetamax)
{
    // draw base of the cone first
    for (int i=0; i<NSEG; i++){


        // get the point
        float p1[4]; //first point of triangle
        float p2[4]; // middle point of triangle
        float p3[4]; // next point of a triangle

        float angle1 = (i / NSEG) * thetamax;
        float angle2 = ((i+1) / NSEG) * thetamax;
        // x1 = x0 + rcos
        p1[0] = radius * cos((angle1/180)*M_PI);
        // y1 = y0 + rsin
        p1[1] = radius * sin((angle1/180)*M_PI);
        // zmin or max
        p1[2] = 0;
        p1[3] = 1;

        // x3 = x0 + rcos
        p3[0] = radius * cos((angle2/180)*M_PI);
        // y3 = y0 + rsin
        p3[1] = radius * sin((angle2/180)*M_PI);
        // z = 0
        p3[2] = 0;
        p3[3] = 1;

        //middle point of triangle
        // x average
        p2[0] = 0;//(p1[0] + p3[0])/2;
        //y average
        p2[1] = 0;//(p1[0] + p3[0])/2;
        // height
        p2[2] = height;
        p2[3] = 1;
        // draw the triangle
        line_pipeline(p1, false);
        line_pipeline(p3, true);
        line_pipeline(p2, true);
        line_pipeline(p1, true);

    }
    // and now the lines
    return RD_OK;
}

int REDirect::rd_cube(void)
{
    float cpoints[8][3] = {{-1,-1,-1}, //0
                            {1,-1,-1}, //1
                            {1,1,-1},  //2
                            {-1,1,-1}, //3
                            {-1,-1,1}, //4
                            {1,-1,1}, //5
                            {1,1,1}, //6
                            {-1,1,1}}; //7

//    float cpoints[8][3] = {{-1,-1,-1}, //0
//                           {-1, -1,1}, //1
//                           {-1,1,-1},  //2
//                           {-1,1,1}, //3
//                           {1,-1,-1}, //4
//                           {1,1,-1}, //5
//                           {1,-1,1}, //6
//                           {1,1,1}}; //7

    int faces[6][5] =  {{0,1,5,4,0},
                        {1,2,6,5,1},
                        {3,2,1,0,3},
                        {4,5,6,7,4},
                        {3,7,6,2,3},
                        {4,7,3,0,4}};


    for(int i=0;i<6;i++){
        for(int j=0;j<5;j++){

            // get the point
            float p[4];
            p[0] = cpoints[faces[i][j]][0];
            p[1] = cpoints[faces[i][j]][1];
            p[2] = cpoints[faces[i][j]][2];
            p[3] = 1;

            if(j==0) {
              //move only
                line_pipeline(p, false);
            }
            else{

                line_pipeline(p,true);
                // move and draw
            }
        }
    }
    return RD_OK;
}

int REDirect::rd_cylinder(float radius, float zmin,
                float zmax, float thetamax)
{

// draw 2 circles at zmin and zmax
//float zcoords[2] = {zmin, zmax};
//    for(int zs=0;zs<2;zs++){
//        for (int i=0; i<NSEG; i++){
//            float angle = i /NSEG;
//
//            // get the point
//            float p[3];
//            // x = x0 + rcos
//            p[0] = radius * cos((angle/180)*M_PI);
//            // y = y0 + rsin
//            p[1] = radius * sin((angle/180)*M_PI);
//            // zmin or max
//            p[2] = zcoords[zs];
//
//            if (i == 0) {
//                //move only
//                line_pipeline(p, false);
//            } else {
//                line_pipeline(p, true);
//                // move and draw
//            }
//        }
//    }

    // draw lines between both the circles


    for(int i = 0 ; i<NSEG;i++){
       // float angle = (i / NSEG) * thetamax;

        float angle1 = (i / NSEG) * thetamax;
        float angle2 = ((i+1) / NSEG) * thetamax;

        float p1[4];
        float p2[4];
        float p3[4];
        float p4[4];

        p1[0] = radius * cos((angle1/180)*M_PI);
        p1[1] = radius * sin((angle1/180)*M_PI);
        p1[2] = zmin;
        p1[3] = 1;

        p2[0] = radius * cos((angle2/180)*M_PI);
        p2[1] = radius * sin((angle2/180)*M_PI);
        p2[2] = zmin;
        p2[3] = 1;

        p3[0] = radius * cos((angle2/180)*M_PI);
        p3[1] = radius * sin((angle2/180)*M_PI);
        p3[2] = zmax;
        p3[3] = 1;

        p4[0] = radius * cos((angle1/180)*M_PI);
        p4[1] = radius * sin((angle1/180)*M_PI);
        p4[2] = zmax;
        p4[3] = 1;

        line_pipeline(p1, false);
        line_pipeline(p2, true);
        line_pipeline(p3, true);
        line_pipeline(p4, true);
        //line_pipeline(p1, true);

    }

    return RD_OK;
}

int REDirect::rd_disk(float height, float radius, float theta)
{
    float NSEG = 12;
    // store indices where the 0, cos and sin occur
    for(float h=0;h<height;h++){
        for (int i=0; i<NSEG; i++){
            float angle = (i / NSEG) * theta;
            // get the point
            float p[3];
            //std::copy(&cpoints[faces[i][j]], &cpoints[faces[i][j]] + 3, &p1[0]);

            // x = x0 + rcos
            p[0] = radius * cos((angle/180)*M_PI);
            // y = y0 + rsin
            p[1] = radius * sin((angle/180)*M_PI);
            // height along z axis
            p[2] = h;

            if (i == 0) {
                //move only
                line_pipeline(p, false);
                //  std::copy(&cpoints[faces[i][j+1]], &cpoints[faces[i][j+1]] + 3, &p2[0]);
            } else {
                line_pipeline(p, true);
                // move and draw
                //std::copy(&cpoints[faces[i][0]], &cpoints[faces[i][0]] + 3, &p2[0]);
            }
        }
    }
    return RD_OK;
}
//
//
//int REDirect::rd_hyperboloid(const float start[3], const float end[3],
//                   float thetamax)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_paraboloid(float rmax, float zmin,
//                  float zmax, float thetamax)
//{
//    return RD_OK;
//}
//
int REDirect::rd_sphere(float radius, float zmin, float zmax, float thetamax)
{
    // store indices where the 0, cos and sin occur
//    int circles[3][3] = {{2,0,1},{0,1,2},{1,0,2}};
//
//    for(int c=0;c<3;c++){
//            for (int i=0; i<=NSEG; i++){
//                float theta = (i / NSEG) * thetamax;
//                // get the point
//                float p[4];
//                //std::copy(&cpoints[faces[i][j]], &cpoints[faces[i][j]] + 3, &p1[0]);
//                // first position in circle array is 0
//                p[circles[c][0]] = 0;
//                // second position in circle array is cos
//                p[circles[c][1]] = -radius * cos((theta/180)*M_PI);
//                // third position in circle array is sin
//                p[circles[c][2]] = -radius * sin((theta/180)*M_PI);
//                p[3] =1;
//                if (i == 0) {
//                    //move only
//                    line_pipeline(p, false);
//                    //  std::copy(&cpoints[faces[i][j+1]], &cpoints[faces[i][j+1]] + 3, &p2[0]);
//                } else {
//                    line_pipeline(p, true);
//                    // move and draw
//                    //std::copy(&cpoints[faces[i][0]], &cpoints[faces[i][0]] + 3, &p2[0]);
//                }
//            }
//    }

// Draw longitudes
    for (int i = 0; i <= NSEG; i++) {
        float theta = i * 2 * (M_PI) / NSEG;
        // draw resolution
        for (int j = 0; j <= NSEG; j++) {
            float phi = j * (M_PI) / NSEG;

            // longitude specs
            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);

            float p[4] = {x, y, z, 1};

            if (j == 0) {
                //move only
                line_pipeline(p, false);
            } else {
                line_pipeline(p, true);
            }
        }
    }

// Draw latitudes
    for(int j = 0; j <= NSEG; j++) {
        float phi = j * (M_PI) / NSEG;
        // draw resolution
        for(int i = 0; i <= NSEG; i++) {
            float theta = i * 2 * (M_PI) / NSEG;
            // longitude specs
            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);

            float p[4] = {x, y, z, 1};

            if (j == 0) {
                //move only
                line_pipeline(p, false);
            } else {
                line_pipeline(p, true);
            }
        }
    }


    return RD_OK;
}
//
//int REDirect::rd_sqsphere(float radius, float north, float east,
//                float zmin, float zmax, float thetamax)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_sqtorus(float radius1, float radius2,
//               float north, float east, float phimin, float phimax,
//               float thetamax)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_torus(float radius1, float radius2,
//             float phimin, float phimax, float thetamax)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_tube(const float start[3], const float end[3], float radius)
//{
//    return RD_OK;
//}
//
//
//
//
/////********************  Lighting & Shading  ***************************/
////
////
////int REDirect::rd_background(const float color[])
////{
////    return RD_OK;
////}
////// red, green, blue by default
////
//
//
//int REDirect::rd_opacity(float opacity)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_emission(const float color[], float intensity)
//{
//    return RD_OK;
//}
//
//
//
//int REDirect::rd_surface(const string & shader_type)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_cone_light(const float pos[3], const float at[3],
//                  float theta_min, float theta_max,
//                  const float color[], float intensity)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_point_light(const float pos[3],
//                   const float color[], float intensity)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_far_light  (const float dir[3],
//                   const float color[], float intensity)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_ambient_light(const float color[], float intensity)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_specular_color(const float color[], int exponent)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_k_ambient(float Ka)
//{
//    return RD_OK;
//}
//int REDirect::rd_k_diffuse(float Kd)
//{
//    return RD_OK;
//}
//int REDirect::rd_k_emission(float Ke)
//{
//    return RD_OK;
//}
//int REDirect::rd_k_specular(float Ks)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_attribute_push(void)
//{
//    return RD_OK;
//}
//int REDirect::rd_attribute_pop(void)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_map_border(const string & map_type,
//                  const string & horizontal,
//                  const string & vertical)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_map_bound(const string & map_type,
//                 float s_min, float t_min,
//                 float s_max, float t_max)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_map_load(const string & filename,
//                const string & label)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_map_sample(const string & map_type,
//                  const string & intra_level,
//                  const string & inter_level)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_map(const string & map_type, const string & label)
//{
//    return RD_OK;
//}
//
//
//
/////****************************  Options  **********************************/
//
//int REDirect::rd_option_array(const string & name, int n, const float *values)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_option_bool(const string & name, bool flag)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_option_list(const string & name, int n, const string values [])
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_option_real(const string & name, float value)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_option_string(const string & name, const string & value)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_custom(const string & label)
//{
//    return RD_OK;
//}
