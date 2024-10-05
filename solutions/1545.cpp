#include <bits/stdc++.h>

using namespace std;

const int MAXN = 19;

int N, A[MAXN][MAXN], cache[MAXN][1<<MAXN];

int dp(int cur, int taken)
{
    if(taken == (1<<N)-1) {
        if(cur == 0) return 0;
        return 1e9;
    }
    if(taken && cur == 0) return 1e9;
    int& ret = cache[cur][taken];
    if(ret != -1) return ret;

    ret = 1e9;
    for(int i = 0; i < N; i++) {
        if(taken&(1<<i) || A[cur][i] == 0) continue;
        ret = min(ret, dp(i, taken|(1<<i)) + A[cur][i]);
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