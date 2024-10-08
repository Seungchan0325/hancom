#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second

using ll = long long;
using pii = pair<ll, ll>;

ll ccw(pii p1, pii p2, pii p3)
{
    return (p2.X - p1.X) * (p3.Y - p1.Y) - (p3.X - p1.X) * (p2.Y - p1.Y);
}

void convexHull(vector<pii>& v)
{
    int N = v.size();
    sort(v.begin(), v.end());
    vector<pii> up, dw;
    for(int i = 0; i < N; i++) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], v[i]) >= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], v[i]) <= 0) dw.pop_back();
        up.push_back(v[i]);
        dw.push_back(v[i]);
    }

    v = dw;
    for(int i = up.size() - 2; i >= 1; i--) v.push_back(up[i]);
}

int main()
{
    int N;
    cin >> N;
    vector<pii> v(N);
    for(auto& [x, y] : v) cin >> x >> y;

    convexHull(v);

    N = v.size();
    ll area = 0;

    for(int i = 0; i < N; i++) {
        area += v[i].X * v[(i+1)%N].Y - v[i].Y * v[(i+1)%N].X;
    }

    if(area % 2) cout << area/2 << ".5";
    else cout << area/2;
}