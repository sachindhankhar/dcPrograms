//compile--> g++ -std=c++11 -fopenmp p1q3.cpp
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
int main(){
    int n;
    cout<<"enter number(upper bound)\n";
    cin>>n;
    vector<bool>primes(n+1,true);
    vector<double>sines(n+1,0.0);
    #pragma omp parallel sections shared(n)
    {
        #pragma omp section
        {
            primes[0]=primes[1]=false;
            for(int i=2;i<=n;++i){
                if(primes[i] && (long long)i*i<=n){
                    for(long long j=i*i;j<=n;j+=i){
                        primes[j]=false;
                    }
                }
            }
        }
        #pragma omp section
        {
            double pi=atan(1)*4;
            for(int i=0;i<=n;++i){
                sines[i]=sin((pi/180)*i);
            }
        }
    }
    cout<<"prime numbers till "<<n<<"\n";
    for(int i=0;i<primes.size();++i){
        if(primes[i]) cout<<i<<" ";
    }cout<<"\n";
    cout<<"sine table till "<<n<<"\n";
    for(int i=0;i<=n;++i) cout<<sines[i]<<" ";
    cout<<"\n";
    return 0;
}