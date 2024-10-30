#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    bool operator < (const Point& rhs) const {
        return x < rhs.x;
    }
};

const int MAXN = 100005;

int N, ans = 1e9;
Point p[MAXN];

int dist(Point p1, Point p2)
{
    int x = p1.x - p2.x;
    int y = p1.y - p2.y;
    return x * x + y * y;
}

void DnC(int l, int r)
{
    if(l == r) return;
    int m = (l + r) / 2;
    DnC(l, m);
    DnC(m+1, r);

    int mx = (p[m].x + p[m+1].x) / 2;
    vector<Point> v;
    for(int i = l; i <= r; i++) {
        if((mx - p[i].x) * (mx - p[i].x) <= ans) {
            v.push_back(p[i]);
        }
    }

    sort(v.begin(), v.end(), [](Point a, Point b) {
        return a.y < b.y;
    });

    for(int i = 0; i < v.size(); i++) {
        for(int j = i+1; j < v.size(); j++) {
            if(dist(v[j], v[i]) >= ans) break;
            ans = min(ans, dist(v[j], v[i]));
        }
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p+1, p+N+1);

    DnC(1, N);
    cout << ans;
}