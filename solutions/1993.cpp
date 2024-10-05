#include <bits/stdc++.h>

using namespace std;

const int MAXN = 12;

int N, cache[MAXN][MAXN][1<<MAXN], cost[256][256];
char G[MAXN][MAXN];

int dp(int i, int j, int taken)
{
    if(i == N) return 0;
    if(j == N) return dp(i+1, 0, taken);
    int& ret = cache[i][j][taken];
    if(ret != -1) return ret;

    if(taken&1) return ret = dp(i, j+1, taken>>1);

    ret = dp(i, j+1, taken>>1);
    if(~taken&2 && j+1 < N) ret = max(ret, dp(i, j+1, (taken|2)>>1) + cost[G[i][j]][G[i][j+1]]);
    if(~taken&(1<<N) && i+1 < N) ret = max(ret, dp(i, j+1, (taken|(1<<N))>>1) + cost[G[i][j]][G[i+1][j]]);

    return ret;
}

int main()
{
    cost['A']['A'] = 100;
    cost['A']['B'] = 70;
    cost['A']['C'] = 40;
    cost['A']['F'] = 0;
    cost['B']['A'] = 70;
    cost['B']['B'] = 50;
    cost['B']['C'] = 30;
    cost['B']['F'] = 0;
    cost['C']['A'] = 40;
    cost['C']['B'] = 30;
    cost['C']['C'] = 20;
    cost['C']['F'] = 0;
    cost['F']['A'] = 0;
    cost['F']['B'] = 0;
    cost['F']['C'] = 0;
    cost['F']['F'] = 0;
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> G[j][i];
        }
    }
    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0, 0);
    cout << result;
}