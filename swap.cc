#include<iostream>
using std::cout;

void swap_points(int &p1, int &p2){
    int temp = p1;
    p1 = p2;
    p2 = temp;
}


int main(){
    int p1 = 4;
    int p2 = 6;

    cout<<p1<<p2;
    swap_points(p1, p2);
    cout<<p1<<p2;
    return(0);
}