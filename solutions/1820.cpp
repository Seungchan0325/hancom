#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second

const int MAXW = 1005;

int N, W, cache[MAXW][MAXW];
pair<int, int> P[MAXW];

int dist(pair<int, int> a, pair<int, int> b)
{
    return abs(a.X - b.X) + abs(a.Y - b.Y);
}

int dp(int i, int j)
{
    if(i == W) return 0;
    if(i < j) return dp(j, i);
    int& ret = cache[i][j];
    if(ret != -1) return ret;
    ret = min(dp(i+1, i) + dist(P[j], P[i+1]), dp(i+1, j) + dist(P[i], P[i+1]));
    return ret;
}

void restruct(int i, int j, int cur)
{
    if(i == W) return;
    if(i < j) {
        restruct(j, i, 3 - cur);
        return;
    }

    if(dp(i+1, i) + dist(P[j], P[i+1]) == dp(i, j)) {
        cout << 3 - cur << "\n";
        restruct(i+1, i, 3 - cur);
    } else {
        cout << cur << "\n";
        restruct(i+1, j, cur);
    }
}

int main()
{
    cin >> N;
    cin >> W;
    for(int i = 0; i < W; i++) {
        cin >> P[i+3].X >> P[i+3].Y;
    }
    P[1] = {1, 1};
    P[2] = {N, N};
    W += 2;

    memset(cache, -1, sizeof(cache));
    int result = dp(1, 2);
    cout << result << "\n";
    restruct(1, 2, 1);
}