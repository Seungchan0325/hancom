#include <bits/stdc++.h>

using namespace std;

const int MAXN = 16;
const int MOD = 10000;

int N, A[MAXN][MAXN], cache[MAXN][1<<MAXN];

int dp(int idx, int taken)
{
    if(idx == N) return 1;
    int& ret = cache[idx][taken];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 0; i < N; i++) {
        if(taken&(1<<i)) continue;
        ret += dp(idx+1, taken|(1<<i)) * A[i][idx] % MOD;
        ret %= MOD;
    }
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0);
    cout << result;
}