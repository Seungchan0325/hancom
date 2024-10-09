#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second

#define X first
#define Y second

using ll = long long;
using pii = pair<ll, ll>;

ll ccw(pii p1, pii p2, pii p3)
{
    ll ret = (p2.X - p1.X) * (p3.Y - p1.Y) - (p2.Y - p1.Y) * (p3.X - p1.X);
    if(ret < 0) return -1;
    else if(ret == 0) return 0;
    else return 1;
}

pair<double, double> line(pair<pii, pii> s)
{
    double a = (double)(s.first.Y - s.second.Y) / (s.first.X - s.second.X);
    double b = (double) -a * s.first.X + s.first.Y;
    return {a, b};
}

pair<double, double> cross(pair<pii, pii> s1, pair<pii, pii> s2)
{
    if(s2.first.X == s2.second.X) swap(s1, s2);

    auto [a2, b2] = line(s2);
    if(s1.first.X == s1.second.X) {
        double y = a2 * s1.first.X + b2;
        return {s1.first.X, y};
    }

    auto [a1, b1] = line(s1);

    double x = (b2 - b1) / (a1 - a2);
    double y = a1 * x + b1;
    return {x, y};
}

bool equal(double a, double b) { return a - b < 1e9; }

int main()
{
    int N;
    cin >> N;
    vector<pair<pii, pii>> v;
    for(int i = 0; i < N; i++) {
        pii p1, p2;
        cin >> p1.X >> p1.Y >> p2.X >> p2.Y;
        pii a[4] = {pii(10, 10), pii(10, -10), pii(-10, -10), pii(-10, 10)};

        bool flag = false;
        for(int j = 0; j < 4; j++) {
            auto s = a[j];
            auto e = a[(j+1)%4];
            if(ccw(s, e, p1) * ccw(s, e, p2) < 0 && ccw(p1, p2, s) * ccw(p1, p2, e) < 0) {
                flag = true;
                break;
            }
        }

        if(p1.X == p1.Y && p2.X == p2.Y)
            flag = true;
        if(p1.X == -p1.Y && p2.X == -p2.Y)
            flag = true;
        
        if(flag) v.emplace_back(p1, p2);
    }


    int ans = 1;

    for(int i = 0; i < v.size(); i++) {
        int cnt = 2;

        for(int j = 0; j < i; j++) {
            auto [x, y] = cross(v[i], v[j]);
            if(-10 < x && x < 10 && -10 < y && y < 10) {
                cnt++;
            }
        }

        ans += max(cnt - 1, 0);
    }
    cout << ans;
}