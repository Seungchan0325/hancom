#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1005;
const ll MOD = 1000000003;

ll N, K, dp[MAXN][MAXN][2];

int main()
{
    cin >> N >> K;

    for(ll i = 0; i < N; i++) dp[i][0][0] = 1;
    dp[1][1][1] = 1;

    for(ll n = 2; n < N; n++) {
        for(ll k = 1; k <= K; k++) {
            dp[n][k][0] = (dp[n-1][k][0] + dp[n-2][k-1][0]) % MOD;
            dp[n][k][1] = (dp[n-1][k][1] + dp[n-2][k-1][1]) % MOD;
        }
    }

    ll result = (dp[N-1][K][0] + dp[N-2][K-1][0] + dp[N-1][K][1]) % MOD;

    cout << result;
}