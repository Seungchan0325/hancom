#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

using ll = long long;

struct Point {
    ll x, y, n;
    Point() : x(0), y(0), n(0) {}
    Point(ll x, ll y, ll n) : x(x), y(y), n(n) {}
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

int N;

int main()
{
    cin >> N;
    vector<Point> apples, cows;
    for(int i = 1; i <= N; i++) {
        int q, t, x, n;
        cin >> q >> t >> x >> n;
        if(q == 1) cows.emplace_back(x, t, n);
        else apples.emplace_back(x, t, n);
    }

    for(auto& [x, y, n] : apples) {
        for(int i = 0; i < 5; i++) {        
            ll tx = x, ty = y;
            x = tx - ty;
            y = tx + ty;
        }
    }
    for(auto& [x, y, n] : cows) {
        for(int i = 0; i < 5; i++) {        
            ll tx = x, ty = y;
            x = tx - ty;
            y = tx + ty;
        }
    }
    sort(apples.begin(), apples.end());
    sort(cows.begin(), cows.end());

    map<ll, ll> m;
    int ans = 0;
    int j = 0;
    for(auto [x, y, n] : apples) {
        while(j < cows.size() && cows[j].x <= x) {
            m[cows[j].y] += cows[j].n;
            j++;
        }
        while(n) {
            auto it = m.lower_bound(y);
            if(it == m.end()) break;
            int v = min(n, it->second);
            ans += v;
            n -= v;
            if((it->second -= v) == 0) {
                m.erase(it);
            }
        }
    }
    cout << ans;
}