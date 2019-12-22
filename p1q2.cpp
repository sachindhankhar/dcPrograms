//compile--> g++ -std=c++11 -fopenmp p1q2.cpp
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
int main(){
    int m,n;
    cout<<"enter size of matrix row*col\n";
    cin>>m>>n;
    vector<vector<int> >matrix;
    cout<<"enter matrix cell values\n";
    for(int i=0;i<m;++i){
        matrix.push_back(vector<int>());
        for(int j=0;j<n;++j){
            int temp;
            cin>>temp;
            matrix[i].push_back(temp);
        }
    }

    cout<<"enter size of vector\n";
    cin>>m;
    vector<int> vec(m,0);
    cout<<"enter vector coeff\n";
    for(int i=0;i<m;++i){
        cin>>vec[i];
    }
    vector<int>res(matrix[0].size(),0);
    #pragma omp parallel for
    for(int i=0;i<matrix[0].size();++i){
        #pragma omp parallel for
        for(int j=0;j<vec.size();++j){
            res[i]+=matrix[j][i]*vec[j];
        }
    }
    cout<<"resultant vector is:\n";
    for(int i=0;i<res.size();++i){
        cout<<res[i]<<" ";
    }cout<<"\n";
    return 0;
}