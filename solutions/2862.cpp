#include <bits/stdc++.h>

using namespace std;

int N, M, cache[305][205];

int dp(int n, int m)
{
    if(m > n) swap(n, m);
    if(n % m == 0) return n / m;

    int& ret = cache[n][m];
    if(ret != -1) return ret;

    ret = 987654321;
    for(int i = 1; i < n; i++) {
        ret = min(ret, dp(i, m) + dp(n-i, m));
    }
    for(int i = 1; i < m; i++) {
        ret = min(ret, dp(n, i) + dp(n, m-i));
    }

    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));
    cin >> N >> M;
    if(M > N) swap(N, M);
    int ans = 0;
    while(N >= 3*M) {
        N -= M;
        ans++;
    }
    ans += dp(N, M);
    cout << ans;
}