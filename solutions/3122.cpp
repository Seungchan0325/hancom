#include <bits/stdc++.h>

using namespace std;

#define int long long
#define X first
#define Y second

const int MAXN = 10005;

using pii = pair<int, int>;

int N, X1[MAXN], Y1[MAXN], X2[MAXN], Y2[MAXN];

int ccw(pii p1, pii p2, pii p3)
{
    int ret = (p2.X - p1.X) * (p3.Y - p1.Y) - (p3.X - p1.X) * (p2.Y - p1.Y);
    if(ret < 0) return -1;
    else if(ret == 0) return 0;
    else return 1;
}

bool is_meet(int i, int j)
{
    pii p1 = {X1[i], Y1[i]};
    pii p2 = {X2[i], Y2[i]};
    pii p3 = {X1[j], Y1[j]};
    pii p4 = {X2[j], Y2[j]};
    if(p1 > p2) swap(p1, p2);
    if(p3 > p4) swap(p3, p4);

    if(p1 == p3 || p2 == p4 || p2 == p3 || p1 == p4) return true;

    int p = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    int q = ccw(p3, p4, p1) * ccw(p3, p4, p2);

    if(p == 0 && q == 0) {
        return p1 <= p4 && p3 <= p2;
    }

    return p <= 0 && q <= 0;
}

signed main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
    }

    int cnt = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j < i; j++) {
            if(is_meet(i, j))
                cnt++;
        }
    }
    cout << cnt;
}