//compile--> g++ -std=c++11 -fopenmp p1q4.cpp
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
int main(){
    int n,res=1;
    cout<<"enter number\n";
    cin>>n;
    #pragma omp parallel for reduction(*:res)
    for(int i=1;i<=n;++i){
        res*=i;
    }
    cout<<"when first private is not used "<<res<<"\n";
    res=1;
    #pragma omp parallel for firstprivate(res)
    for(int i=1;i<=n;++i){
        res*=i;
    }
    cout<<"when first private is used "<<res<<"\n";
    return 0;
}