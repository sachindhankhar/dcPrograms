//to compile --> g++ -fopenmp -std=c++11 p1q6.cpp -lgd
//to install gd in ubuntu --> sudo apt install libgd-dev
#include<bits/stdc++.h>
#include<gd.h>
#include<omp.h>
using namespace std;
int main(){
    FILE *fp=fopen("inputImage.png","r");
    gdImagePtr img=gdImageCreateFromPng(fp);
    int width=gdImageSX(img);
    int height=gdImageSY(img);
    #pragma omp parallel for num_threads(4)
    for(int i=0;i<width;++i){
        for(int j=0;j<height;++j){
            int color=gdImageGetPixel(img,i,j);
            int red=gdImageRed(img,color);
            int green=gdImageGreen(img,color);
            int blue=gdImageBlue(img,color);
            int avg=(red+green+blue)/3;
            color=gdImageColorAllocate(img,avg,avg,avg);
            gdImageSetPixel(img,i,j,color);
        }
    }
    fp=fopen("outputImage.png","w");
    gdImagePng(img,fp);
    gdImageDestroy(img);
    fclose(fp);
    return 0;
}
