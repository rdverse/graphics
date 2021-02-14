#include "rd_direct.h"
#include "rd_error.h"
#include "rd_display.h"
#include "iostream"
#include <string>
using std::string;
using std::cout;




//General Functions
int REDirect::rd_display(const string & name, const string & type, const string & mode)
{
    return RD_OK;
}

int REDirect::rd_format(int xresolution, int yresolution)
{
    std::cout<<xresolution<<yresolution;
    return RD_OK;
}

int REDirect::rd_world_begin(void)
{
    rd_disp_init_frame(1);
    cout<<"Beginning the world";
    return RD_OK;
}
int REDirect::rd_world_end(void)
{
    rd_disp_end_display();
    return RD_OK;
}

int REDirect::rd_frame_begin(int frame_no)
{
    cout<<frame_no;
    cout<<display_ySize;
    //frame_number = frame_no;
    return RD_OK;
}
int REDirect::rd_frame_end(void)
{
    // Same as rd_world end, will change later
    rd_disp_end_display();
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

//int REDirect::rd_background(const float color[]) {
    //int status;
//    rd_disp_init_frame(1);
//    cout<<"Here is the color for the background : {}"<<color;
//    screen_background_color[0] = color[0];
//    screen_background_color[1] = color[1];
//    screen_background_color[2] = color[2];
//    // status = rd_set_background(screen_background_color);
//    rd_set_background(screen_background_color);
//    return(RD_OK);
//}

//// red, green, blue by default
//
//int REDirect::rd_color(const float color[])
//{
    // store values of rg b in a flobal location as current drawing color/.
    // default is white
//    cout<<"rd_Color in rd_direct  is accessed";
//    current_drawing_color[0] = color[0];
//    current_drawing_color[1] = color[1];
//    current_drawing_color[2] = color[2];

//    return RD_OK;
//}
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