//compile--> g++ -std=c++11 -fopenmp p1q5.cpp
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
int main(){
    pair<int,int>c1(1,1),c2(4,4),c3(8,8);
    vector<pair<int,int> >centroids;
    centroids.push_back(c1);
    centroids.push_back(c2);
    centroids.push_back(c3);
    int n;
    cout<<"enter no. of points\n";
    cin>>n;
    vector<pair<int,int> >points;
    for(int i=0;i<n;++i){
        int x,y;
        cout<<"enter x,y coordinates\n";
        cin>>x>>y;
        points.push_back(make_pair(x,y));
    }

    cout<<"serial computation\n";
    for(int i=0;i<points.size();++i){
        double mindis=10000;
        int cluster=0;
        for(int j=0;j<centroids.size();++j){
            double dis=sqrt(pow(centroids[j].first-points[i].first,2)+pow(centroids[j].second-points[i].second,2));
            if(dis<mindis){
                mindis=dis;
                cluster=j;
            }
        }
        cout<<"point ("<<points[i].first<<" , "<<points[i].second<<") belong to cluster ("<<centroids[cluster].first<<" , "<<centroids[cluster].second<<")\n";
    }


    cout<<"parallel computation\n";
    #pragma omp parallel for
    for(int i=0;i<points.size();++i){
        double mindis=10000;
        int cluster=0;
        #pragma omp parallel for
        for(int j=0;j<centroids.size();++j){
            double dis=sqrt(pow(centroids[j].first-points[i].first,2)+pow(centroids[j].second-points[i].second,2));
            if(dis<mindis){
                mindis=dis;
                cluster=j;
            }
        }
        cout<<"point ("<<points[i].first<<" , "<<points[i].second<<") belong to cluster ("<<centroids[cluster].first<<" , "<<centroids[cluster].second<<")\n";
    }
    return 0;
}