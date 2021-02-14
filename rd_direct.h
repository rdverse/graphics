#ifndef RD_ENGINE_DIRECT_H
#define RD_ENGINE_DIRECT_H

#include "rd_enginebase.h"
#include "rd_display.h"
#include <string>
using std::string;

// This is a rendering engine that renders directly to the image buffer as
// primitives come in.  A depth buffer is obviously needed.  Transparency is
// not properly handled.

// float current_drawing_color[] = {0.5, 0.5,1};
// float screen_background_color[] = {1, 0.5,1};


class REDirect: public RenderEngine
{
 public:
  // Only methods inherited from the RenderEngine class should be added here,
//  // as needed.
int rd_display(const string & name, const string & type,
			 const string & mode);

int rd_format(int xresolution, int yresolution);

int rd_world_begin(void);

int rd_world_end(void);

int rd_frame_begin(int frame_no);

int rd_frame_end(void);

 int rd_render_init(void);  /* Initialize renderer */

 int rd_render_cleanup(void);

// int rd_background(const float color[]);
//
// int rd_color(const float color[]);
//
// int rd_point(const float p[3]);


};

#endif /* RD_ENGINE_DIRECT_H */
