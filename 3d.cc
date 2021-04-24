#include<iostream>
#include<stdio.h>


int main(){
    double arr[2][4][4];

    for(int k=0;k<2;k++){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                arr[k][i][j] = k;
            }
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            std::cout<<arr[1][i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    return 0;
}