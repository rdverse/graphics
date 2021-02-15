#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <fstream>
using std::ios;
using std::ofstream;

int main()
{
  const int XSIZE = 400;
  const int YSIZE = 400;
  
  ofstream out;

  out.open("test.ppm", ios::binary);

  // Print header

  out << "P6\n" << XSIZE << " " << YSIZE << "\n255\n";

  for (int y = 0; y < YSIZE; y++)
    {
      for(int x = 0; x < XSIZE; x++)
	{
	  out.put(int(((float)x/XSIZE)*255)); // Red
	  out.put(int(((float)y/YSIZE)*255)); // Green
	  out.put(0.4); // Blue
	}
    }

  out.close();

  return 0;
}
