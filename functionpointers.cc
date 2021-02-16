#include<iostream>

using std::endl;
using std::cout;

//int (* rd_set_background)(int x, int y,const float rgb []){
//    cout<<"Gello";
//    cout<<x<<endl;
//    cout<<y<<endl;
//    cout<<rgb<<endl;
//    return 1;
//}

int plot_a_reference(const float color []){

    cout<<color[1];
}

int main() {
//    typedef int(*callfun)(int, int, const float *);
//
//    callfun cf = rd_set_background;


//    auto cf = int(* callfun)(int, int, const float *);
//    const float rgbv[3] = {1.0,2.0,3.0};
//    int a;
//    a = cf(1,2, (const float*)rgbv);

    float b = 10.6;
    int a = int(b);
    cout<<a;

    const float colors[3] = {1.234, 4.212, 2.3};
    a = plot_a_reference(&colors[0]);

    //auto callfun = &rd_set_background(int, int, const float*);

//    const float rgbv[3] = {1.0,2.0,3.0};
//    int a;
//    //const float* rgbvf = (const float*)rgbv;
//    a = cf(1,2, (const float*)rgbv);
//    cout<<a;
    return(0);
}


