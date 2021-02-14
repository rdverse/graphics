#include <iostream>
#include "global.h"
//extern const int frame_no;

int foo(const float b[]){
 //   frame_no =10;
  //  std::cout<<frame_no;
  std::cout<<global_c;
  global_c = 88;
    return b[0];
}

void foo1(void){
    int c=500;
    std::cout<<c<<global_c<<"foo1";
 //   frame_no= 20;
  //  std::cout<<frame_no;
}

void foo3(void){
    const float arr[] = {0.1,0.2,0.3};
    const float* arr2;
    arr2 = arr;
//std::copy(std::begin(arr), std::end(arr), std::begin(arr2));
    std::cout<<std::endl<<*arr2;
}


int main(){
    int (* a)(const float b []) = &foo;
    const float b[] = {1.3, 2.5};
    std::cout << a(b) << std::endl;
   foo1();
   foo3();

   //std::cout<<c;
    return 0;
}
