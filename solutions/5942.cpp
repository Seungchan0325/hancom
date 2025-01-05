#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 5050;
const int MOD = 1e9 + 7;

int N, K, DP[MAXN][MAXN], PSUM[MAXN][MAXN];

int main()
{
    cin >> N >> K;

    DP[1][1] = DP[2][2] = PSUM[1][1] = PSUM[2][2] = 1;
    for(int i = 3; i <= N; i+=2) PSUM[i][1] = PSUM[i-2][1];
    for(int i = 4; i <= N; i+=2) PSUM[i][2] = PSUM[i-2][2];
    for(int i = 3; i <= N; i++) {
        for(int j = 3; j <= i; j++) {
            DP[i][j] = (PSUM[i-1][j-1] + PSUM[i-j+1][j-1]) % MOD;
            PSUM[i][j] = (PSUM[i-2][j] + DP[i][j]) % MOD;
        }
    }

    int ans = 0;
    for(int i = 2; i <= N; i++) {
        for(int j = 1; j <= min(N, K); j++) {
            ans = (ans + (ll)2*DP[i][j]*(K-j+1)%MOD) % MOD;
        }
    }
    cout << ans;
}