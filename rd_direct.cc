//added
#include<iostream>
#include "rd_direct.h"
#include "rd_error.h"
#include "rd_display.h"

#include <string>
using std::string;

// global variable to store frame_no
int frame_number;
// store value of current color in global value
float DrawColor[3] = {0.0, 0.0, 0.0};
//const float color_black[3] = {100,0,0};
//const int X_resolution;
//const int Y_resolution;
float BackgroundColor[3] = {1.0 ,  1.0 , 1.0};


int REDirect::rd_display(const string & name, const string & type, const string & mode)
{
    // Nothing to implement in this function, everthing is done behind the scenes
    return RD_OK;
}

int REDirect::rd_format(int xresolution, int yresolution)
{

    // store values of resolution in global variables. This is required in pnm
     std::cout<<xresolution<<yresolution;
    return RD_OK;
}


int REDirect::rd_frame_begin(int frame_no)
{
    // Store the frame value in a global variable
   // rd_disp_init_frame(frame_number);
    frame_number = frame_no;
    //Calling world begin or init frame will give error
    return RD_OK;
}

int REDirect::rd_world_begin(void) {
    //initialize display for new image, use below function
    // float testreturn[3] = {0,0,0};
    // rd_write_pixel(10,10, testreturn);
    //rd_print_error(RD_OK, "s01.rd");
    try {
//        rd_disp_init_frame(frame_number);
//        rd_clear();
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


int REDirect::rd_render_init(void)
{
    return RD_OK;
}

int REDirect::rd_render_cleanup(void)
{
    return RD_OK;
}

int REDirect::rd_color(const float color[])
{
    // Copy the color contents into global drawColor
    DrawColor[0] = color[0];
    DrawColor[1] = color[1];
    DrawColor[2] = color[2];
    return RD_OK;
}

 int REDirect::rd_point(const float p[3]){
    // ONly have to write the pixel at the given co-ordinates
    return(rd_write_pixel(p[0],p[1], &DrawColor[0]));
}

 int REDirect::rd_background(const float color[]) {
    BackgroundColor[0] = color[0];
     BackgroundColor[0] = color[1];
     BackgroundColor[0] = color[2];
    return (rd_set_background(&BackgroundColor[0]));
}

     //  rd_clear();
     // std::cout<<color;

//    typedef int(*)(int, int, const float*)

     //    std::cout<<color;
     //  rd_clear();
     // const float* backgroundColor = (const float*)color_black;
     //  const float drawing_colors[3] = {0.2,1.0,0.2};
     //       int a;
     //   a =rd_write_pixel(10,10, &drawing_colors[0]);
//     a =rd_write_pixel(0,2, &drawing_colors[0]);
//
//     a =rd_write_pixel(0,3, &drawing_colors[0]);
//
//     a =rd_write_pixel(0,4, &drawing_colors[0]);
//
//     a =rd_write_pixel(0,5, &drawing_colors[0]);
//
     //   rd_point(color_black);
//     rd_set_background(&color_black[0]);
     // rd_clear();
//     a = rd_write_pixel(0,6, &drawing_colors[0]);
     //   std::cout<<a;
     //const float points[3] = {1,2,3};
     //rd_clear();
     //std::cout<<REDirect::rd_point(points);

     // rd_clear();
//    return(RD_OK);
//backgroundfunc()




int REDirect::rd_line(const float start[3], const float end[3]){
    float xs = start[0];
    float ys = start[1];

    float xe = end[0];
    float ye = end[1];

    float x = xs;
    float y = ys;

    float dx = xe - xs;
    float dy = ye - ys;

    float po = 2*dx - 2*dy;
    float p;

    while(x<xe){
        rd_write_pixel(int(x), int(y), DrawColor);
        x++;
        p = po;
        if(p<0){
            //y = y;
            p = p + 2*dy;
        } else if (p>0){
            y = y + 1;
            p = p + (2*dy - 2*dx);

        }
        else{
            std::cerr<<RD_INPUT_ILLEGAL_FLAG_VALUE;
        }
    }
    return(RD_OK);
}

int REDirect::rd_circle(const float center[3], float radius)
{
    float po = 1 - radius;
    float x = center[0];
    float y = center[1];

    float p = po;

    while(x<y){
        rd_write_pixel(int(x),int(y),DrawColor);
        x++;
        if(p<0){
            p = p + 2*x +1;
        }
        else if(p>0){
            p = p + (2*x - 2*y + 3);
            y--;
        }
        else{
            std::cerr<<RD_INPUT_ILLEGAL_FLAG_VALUE;
        }
    }
    return RD_OK;
}

 int REDirect::rd_fill(const float seed_point[3]){

    float x = seed_point[0];
    float y = seed_point[1];

     const float* fill_color = DrawColor;
     const float* seed_color = DrawColor;
             //rd_read_pixel(x, y, fill_color);

     if(seed_color == fill_color) {

         rd_write_pixel(x, y, fill_color);
        // implement boundary checking later when this command works
        // Following the name convention of WASD as arrow indications for the four point fill algorithm
        const float D[3] = {x+1,y,0};
         const float A[3] = {x-1,y,0};
         const float W[3] = {x,y+1,0};
         const float S[3] = {x,y-1,0};
         rd_fill(D);
         rd_fill(A);
         rd_fill(W);
         rd_fill(S);
     }
    return(RD_OK);
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

////
/////**********************   Transformations **********************************/
//
//int REDirect::rd_translate(const float offset[3])
//{
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
//int REDirect::rd_pointset(const string & vertex_type,
//                int nvertex, const float * vertex)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_polyset(const string & vertex_type,
//               int nvertex, const float * vertex,
//               int nface,   const int * face)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_cone(float height, float radius, float thetamax)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_cube(void)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_cylinder(float radius, float zmin,
//                float zmax, float thetamax)
//{
//    return RD_OK;
//}
//
//int REDirect::rd_disk(float height, float radius, float theta)
//{
//    return RD_OK;
//}
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
//int REDirect::rd_sphere(float radius, float zmin, float zmax, float thetamax)
//{
//    return RD_OK;
//}
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
//int REDirect::rd_fill(const float seed_point[3])
//{
//    return RD_OK;
//}
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