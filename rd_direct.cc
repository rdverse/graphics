//added
#include<iostream>
#include "rd_direct.h"
#include "rd_error.h"
#include "rd_display.h"
#include<math.h>

#include <string>
using std::string;

// global variable to store frame_no
int frame_number;
// store value of current color in global value
 float DrawColor[] = {1.0, 1.0, 1.0};
//const float color_black[3] = {100,0,0};
//const int X_resolution;
//const int Y_resolution;
 float BackgroundColor[] = {0.0 ,  0.0 , 0.0};


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
    return(rd_write_pixel(p[0],p[1], DrawColor));
}

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


int REDirect::rd_line(const float start[3], const float end[3]){

    // Read the coordinates of line start point
    float xs = start[0];
    float ys = start[1];

    // Read coordinates of line end point
    float xe = end[0];
    float ye = end[1];

    // Calculate dx (start-end)x
    float dx = xe - xs;

    // if dx<0, swap end points (by reference)
    if(dx<0){
        swap_points(xs, xe);
        swap_points(ys, ye);
    }
    
    float x = xs;
    float y = ys;
    // calculate new dx
    dx = xe - xs;
    // Calculate dy
    float dy = ye - ys;

    //Initial P
    float p;
    p =  2*dx - 2*dy;

    // Is the line going upwards or downwards?
    char lineType;
    if(dy<0){
        lineType = 'U';
    }
    else{
        lineType = 'D';
    }

    while(x<=xe){
        // Draw the first point
        rd_write_pixel(int(x), int(y), DrawColor);

        if(p<0){
            //No change in y;
            // Only p changes
            p = p + 2*dy;
        //    y--;

        } else if (p>=0){
            // update p
            p = p + (2*dy - 2*dx);
            y++;
            // y increases if line goes up or conditionally decrement
//            std::cout<<lineType;
//            y++;
//            switch (lineType) {
//                case 'U':
//                    y++;
//                    std::cout<<"y incremented";
//                    break;
//                case 'D':
//                    y--;
//                    std::cout<<"y decremented";
//                    break;
//            }
        }
        //In any case increment x (also conditional i guess)
        x++;
    }
    return(RD_OK);
}

void REDirect::line_more_horizontal()
{



}





int REDirect::rd_circle(const float center[3], float radius)
{
    float po = 1 - radius;
    int x = 0;
    int y = radius;
    int xp = int(center[0]);
    int yp = int(center[1]);
    //std::cout<<"x "<<x<<"y "<<y;
    float p = po;

    //float combinations[8][2] = {{x,y}, {y,x}, {-x,-y}, {-y,-x}, {-x, y}, {y,-x}};
    //plot each of the combinations (8)
//    for(int i = 0; i<8; i++) {
//        int x_plot = combinations[i][0];
//        int y_plot = combinations[i][1];
//
//        if (x_plot < y_plot) {
//            circle_plot_function(x_plot, y_plot, x_plot, y_plot, p);
//        }
//        else{
//            circle_plot_function(x_plot, y_plot, x_plot, y_plot, p);
//        }
//    }

    while(y>=x){
        circle_plot_points(x,y,xp,yp);
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

void REDirect::circle_plot_points(int x, int y, int xp, int yp){
    rd_write_pixel(xp+x, yp+y, DrawColor);
    rd_write_pixel(xp-x, yp+y, DrawColor);
    rd_write_pixel(xp+x, yp-y, DrawColor);
    rd_write_pixel(xp-x, yp-y, DrawColor);
    rd_write_pixel(xp+y, yp+x, DrawColor);
    rd_write_pixel(xp-y, yp+x, DrawColor);
    rd_write_pixel(xp+y, yp-x, DrawColor);
    rd_write_pixel(xp-y, yp-x, DrawColor);
}

double round_up_ceil(double value, int decimal_points = 1) {
    const double multiplier = std::pow(10.0, decimal_points);
    return(std::ceil(value * multiplier) / multiplier);
}

 int REDirect::rd_fill(const float seed_point[3]){

fill_helper(int(seed_point[0]), int(seed_point[1]));

return(RD_OK);
}

void REDirect::fill_helper(int x, int y){
    float seed_color[3];
    //pass seed color as a reference and get seed color
    rd_read_pixel(x,y,&seed_color[0]);

    // Remembering graphics is sometimes a hack,
    // The color read is not exact and has a lot of decimals
    // ceiling the values
    seed_color[0] = round_up_ceil(seed_color[0]);
    seed_color[1] = round_up_ceil(seed_color[1]);
    seed_color[2] = round_up_ceil(seed_color[2]);

   // std::cout<<"Seed colors : "<<seed_color[0]<<" "<<seed_color[1]<<" "<<seed_color[2]<<std::endl;

//     std::cout<<"Seed colors : "<<seed_color[0]<<" "<<seed_color[1]<<" "<<

    //int x = int(seed_point[0]);
    //int y = int(seed_point[1]);
   // std::cout<<"seed points"<<x<<"  "<<y<<" "<<seed_point[2]<<std::endl;

    if(boundary_check(x,y)){
        return;
    }

    else if( ( (seed_color[0]!=BackgroundColor[0]) && (seed_color[1]!=BackgroundColor[1]) && (seed_color[2]!=BackgroundColor[2]) ) ) {
        return;
    }

    //std::cout<<"Seed colors : "<<seed_color[0]<<" "<<seed_color[1]<<" "<<seed_color[2]<<std::endl;
    //std::cout<<"Background colors : "<<BackgroundColor[0]<<" "<<BackgroundColor[1]<<" "<<BackgroundColor[2]<<std::endl;

 //   std::cout<<"x "<<x<<" y "<<y<<std::endl;
    rd_write_pixel(x, y, DrawColor);

    //     std::cout<<"display sizes"<<display_xSize<<"  "<<display_ySize<<std::endl;

//     std::cout<<"D vals"<<D[0]<<"  "<<D[1]<<"  "<<D[2]<<std::endl;

    // implement boundary checking later when this command works
    // Following the name convention of WASD as arrow indications for the four point fill algorithm
   //  float D[] = {float(x+1),float(y),0.0};

    int D[2] = {x+1, y};
    int A[2] = {x-1, y};
    int W[2] = {x, y+1};
    int S[2] = {x, y-1};

//    if(check_fill_condition(D[0], D[1])&&check_fill_condition(A[0], A[1])&&check_fill_condition(W[0], W[1])&&check_fill_condition(S[0], S[1])){
//        return(false);
//    }


    fill_helper(D[0], D[1]);
    fill_helper(A[0], A[1]);
    fill_helper(W[0], W[1]);
    fill_helper(S[0], S[1]);

}

bool REDirect::boundary_check(int x, int y){
    if((x<4)||(x>(display_xSize-4))||(y<4)||(y>(display_ySize-4)))
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