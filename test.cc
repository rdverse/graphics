#include <iostream>
using namespace std;

// Base class
class Shape 
{
public:
	Shape(int l, int w)
	{
		length = l;
		width = w;
	} // default constructor
  virtual int get_Area();
	// {
	// 	cout << "This is call to parent class area" << endl;
	// }

protected:
	int length, width;
};

// Derived class
class Square : public Shape 
{

public:
	Square(int l = 0, int w = 0)
		: Shape(l, w)
	{
	} // declaring and initializing derived class
	// constructor
	int get_Area()
	{
		cout << "Square area: " << length * width << endl;
		return (length * width);
	}
};
// Derived class
class Rectangle : public Shape 
{
public:
	Rectangle(int l = 0, int w = 0)
		: Shape(l, w)
	{
	} // declaring and initializing derived class
	// constructor
	int get_Area()
	{
		cout << "Rectangle area: " << length * width
			<< endl;
		return (length * width);
	}
};


void foo3(const float rgb[]){
   std::cout<<rgb[0]<<rgb[1]<<rgb[2];

}

int main(void)
{
//	Shape* s;
//	Square sq(5, 5); // making object of child class Sqaure
//	Rectangle rec(
//		4, 5); // making object of child class Rectangle
//
//	s = &sq;
//	s->get_Area();
//	s = &rec;
//	s->get_Area();
const float arr[3] = {0.4,0.2,0.8};
foo3(arr);
 	return 0;
}
