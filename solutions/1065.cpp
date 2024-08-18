#include <bits/stdc++.h>

using namespace std;

const int MOD = 10000000;
const int MAXN = 105;

int cache[MAXN][MAXN];

int DP(int n, int t)
{
    if(n == 0) return 1;
    int& ret = cache[n][t];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 1; i <= n; i++) {
        ret = (ret + (t + i - 1) * DP(n - i, i) % MOD) % MOD;
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    memset(cache, -1, sizeof(cache));

    int tc;
    cin >> tc;
    while(tc--) {
        int n;
        cin >> n;
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            ans = (ans + DP(n-i, i)) % MOD;
        }
        cout << ans << "\n";
    }
}