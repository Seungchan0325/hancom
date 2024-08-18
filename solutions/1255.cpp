#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin>>N;
    vector<double> v(N);
    for(auto&i:v)cin>>i;
    sort(v.begin(), v.end());
    double ans=INFINITY;
    do{
        vector<double> pos(N);
        pos[0]=v[0];
        for(int i=1;i<N;i++){
            double mx=0;
            for(int j=0;j<i;j++) {
                mx=max(mx,pos[j]+2*sqrt(v[i]*v[j]));
            }
            pos[i]=max(mx,v[i]);
        }
        double mx=0;
        for(int i=0;i<N;i++)mx=max(mx,pos[i]+v[i]);
        ans=min(mx,ans);
    }while(next_permutation(v.begin(),v.end()));
    printf("%.3f",ans);
}