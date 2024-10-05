#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

int N, cost[MAXN][MAXN], cache[MAXN][1<<MAXN], ans[MAXN];

int dp(int idx, int taken)
{
    if(idx == N) return 0;
    int& ret = cache[idx][taken];
    if(ret != -1) return ret;

    ret = 1e9;
    for(int i = 0; i < N; i++) {
        if(taken&(1<<i)) continue;
        ret = min(ret, dp(idx+1, taken|(1<<i)) + cost[i][idx]);
    }
    return ret;
}

void restruct(int idx, int taken)
{
    if(idx == N) return;

    for(int i = 0; i < N; i++) {
        if(taken&(1<<i)) continue;
        if(dp(idx, taken) == dp(idx+1, taken|(1<<i)) + cost[i][idx]) {
            ans[i] = idx;
            restruct(idx+1, taken|(1<<i));
            return;
        }
    }
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> cost[i][j];
        }
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0);
    cout << result << "\n";
    restruct(0, 0);
    for(int i = 0; i < N; i++) cout << ans[i] + 1 << " ";
}