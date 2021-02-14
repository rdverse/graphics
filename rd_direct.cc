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
const float* Color;

//General Functions
int REDirect::rd_display(const string & name, const string & type, const string & mode)
{

    return RD_OK;
}

int REDirect::rd_format(int xresolution, int yresolution)
{
    // store values of resolution in global variables, we might need them later
    std::cout<<xresolution<<yresolution;
    return RD_OK;
}

int REDirect::rd_world_begin(void)
{
    std::cout<<"Entered world loop";
//    int status;
    //rd_disp_init_frame();
    rd_disp_init_display();
    try{
        //rd_disp_init_display();
    }
    catch(std::exception &e){
        std::cerr<<RD_INPUT_DISPLAY_INITIALIZATION_ERROR;
    }
    std::cout<<"From the redirect block inititalizing the display";
    rd_clear();
    return RD_OK;
}
int REDirect::rd_world_end(void)
{
    std::cout<<"world ended";
    rd_disp_end_display();
    return RD_OK;
}

int REDirect::rd_frame_begin(int frame_no)
{
    // store the frame value in a global variable
  //  rd_disp_init_frame(frame_no);
    frame_number = frame_no;
    std::cout<<"Frame number stored"<<frame_number;
    return RD_OK;
}
int REDirect::rd_frame_end(void)
{
    rd_disp_end_frame();
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
    // save color value in a global value
    Color = color;
    return RD_OK;
}

 int REDirect::rd_point(const float p[3]){
//    const float drawing_colors[3] = {0.2,0.2,0.2};
//  rd_write_pixel(10,10, drawing_colors);
     return(RD_OK);
}

 int REDirect::rd_background(const float color[]){
   //  rd_clear();
    // std::cout<<color;
     //const float color_black[3] = {1,0,0};
     //rd_set_background(color);
     return(RD_OK);
 }


/**********Camera*************************/
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
//
///**********************   Transformations **********************************/
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
//
///**********************   Geometric Objects  *******************************/
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
//int REDirect::rd_circle(const float center[3], float radius)
//{
//    return RD_OK;
//}
//
//
//int REDirect::rd_line(const float start[3], const float end[3])
//{
//    return RD_OK;
//}
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
//int REDirect::rd_point(const float p[3])
//{
//    return RD_OK;
//}
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
///********************  Lighting & Shading  ***************************/
//
//
//int REDirect::rd_background(const float color[])
//{
//    return RD_OK;
//}
//// red, green, blue by default
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
///****************************  Options  **********************************/
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