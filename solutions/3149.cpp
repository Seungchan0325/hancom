#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 3005;

int M, N, P[MAXN], cache[MAXN][MAXN];

int dist(int i, int j) { return abs(i - j); }

int dp(int i, int j)
{
    if(i < j) return dp(j, i);
    if(i == N+1) return 0;
    int& ret = cache[i][j];
    if(ret != -1) return ret;
    ret = min(dp(i+1, i) + dist(P[j], P[i+1]), dp(i+1, j) + dist(P[i], P[i+1]));
    return ret;
}

signed main()
{
    cin >> M;
    cin >> P[0] >> P[1];
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> P[i+2];
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 1);
    cout << result;
}