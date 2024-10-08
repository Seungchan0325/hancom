#include <bits/stdc++.h>

using namespace std;

const int MAXN = 25;

int N, X1[MAXN], Y1[MAXN], X2[MAXN], Y2[MAXN];

int ccw(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
}

bool is_intersect(int i, int j)
{
    return (ccw(X1[i], Y1[i], X2[i], Y2[i], X1[j], Y1[j]) * ccw(X1[i], Y1[i], X2[i], Y2[i], X2[j], Y2[j]) <= 0)
    && (ccw(X1[j], Y1[j], X2[j], Y2[j], X1[i], Y1[i]) * ccw(X1[j], Y1[j], X2[j], Y2[j], X2[i], Y2[i]) <= 0);
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
    }

    int cnt = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j < i; j++) {
            if(is_intersect(i, j)) cnt++;
        }
    }
    cout << cnt;
}