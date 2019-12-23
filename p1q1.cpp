//compile--> g++ -std=c++11 -fopenmp p1q1.cpp
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
vector<int> merge(vector<int>vec,int p,int q,int r){
    vector<int>left(vec.begin()+p,vec.begin()+q+1),right(vec.begin()+q+1,vec.begin()+r+1);
    int k=p,i=0,j=0;
    while(i<left.size() && j<right.size()){
        if(left[i]<right[j]){
            vec[k]=left[i];
            ++i;
        }else{
            vec[k]=right[j];
            ++j;
        }
        ++k;
    }
    if(i<left.size()){
        for(int x=i;x<left.size();++x){
            vec[k]=left[x];
            ++k;
        }
    }
    if(j<right.size()){
        for(int x=j;x<right.size();++x){
            vec[k]=right[x];
            ++k;
        }
    }
    return vec;
}
vector<int> mergeSort(vector<int>vec,int start,int end){
    if(start<end){
        int middle=(start+end)/2;

        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                {
                    vector<int> temp;
                    temp=mergeSort(vec,start,middle);
                    #pragma omp critical
                    {
                        #pragma omp parallel for
                        for(int i=start;i<=middle;++i) vec[i]=temp[i];
                    }
                }
                #pragma omp section
                {
                    vector<int> temp;
                    temp=mergeSort(vec,middle+1,end);
                    #pragma omp critical
                    {
                        #pragma omp parallel for
                        for(int i=middle+1;i<=end;++i) vec[i]=temp[i];
                    }

                }
            }
            #pragma omp barrier
            vec=merge(vec,start,middle,end);
        }
    }
    return vec;
}
int main(){
    int n;
    cout<<"enter size of array\n";
    cin>>n;
    vector<int> vec(n,0);
    cout<<"enter elements\n";
    for(int i=0;i<n;++i) cin>>vec[i];
    vec=mergeSort(vec,0,vec.size()-1);
    for(int i=0;i<vec.size();++i) cout<<vec[i]<<" ";
    cout<<"\n";
    return 0;
}
