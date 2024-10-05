#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 11;

int N, M, cache[MAXN][MAXN][1<<MAXN];

int dp(int i, int j, int taken)
{
    if(i == N) return taken == 0 ? 1 : 0;
    if(j == M) return dp(i+1, 0, taken);
    int& ret = cache[i][j][taken];
    if(ret != -1) return ret;

    if(taken&1) return ret = dp(i, j+1, taken>>1);
    
    ret = 0;
    if(~taken&2 && j+2 <= M) ret += dp(i, j+2, taken>>2);
    if(~taken&(1<<M)) ret += dp(i, j+1, (taken|(1<<M))>>1);

    return ret;
}

signed main()
{
    cin >> N >> M;
    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0, 0);
    cout << result;
}