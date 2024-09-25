#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 9;
const ll MAXN = 1000002;

int N, K, cache[MAXN][2][6];

ll dp(int n, int type, int matched)
{
    if(matched >= 5) return 0;
    if(n == N+1) return 1;

    int& ret = cache[n][type][matched];
    if(ret != -1) return ret;
    
    if(matched == 4 && type == 1)
        ret = ((K-2) * dp(n+1, 0, 0) + dp(n+1, 1, 3)) % MOD;
    else if(matched == 2)
        ret = ((K-2) * dp(n+1, 0, 0) + dp(n+1, 0, matched+1) + dp(n+1, 1, matched+1)) % MOD;
    else if(matched == 0)
        ret = ((K-1) * dp(n+1, 0, 0) + dp(n+1, type, matched+1)) % MOD;
    else
        ret = ((K-2) * dp(n+1, 0, 0) + dp(n+1, 0, 1) + dp(n+1, type, matched+1)) % MOD;

    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));
    cin >> N >> K;
    // 호출 깊이 낮추기
    for(int i = N+1; i >= 1; i--) for(int j = 0; j <= 5; j++) {
        dp(i, 0, j);
        dp(i, 1, j);
    }
    ll result = dp(1, 0, 0);
    cout << result;
}