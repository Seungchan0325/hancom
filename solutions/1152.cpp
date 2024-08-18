#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 25;
const ll MAXT = 1000005;
const ll MOD = 1e9 + 7;

ll N, T, bino[MAXN][MAXN], DP[2][MAXT];

int main()
{
    cin >> N >> T;

    if(N >= MAXN) {
        cout << "0";
        return 0;
    }

    for(int i = 1; i <= N; i++) {
        bino[i][1] = 1;
        for(int j = 2; j <= i; j++) {
            bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
        }
    }

    DP[0][0] = 1;
    for(int n = 1; n <= N; n++) {
        for(int i = 0; i <= T; i++) DP[n%2][i] = 0;
        for(int t = bino[N][n]; t <= T; t++) {
            DP[n%2][t] = (DP[(n-1)%2][t-bino[N][n]] + DP[n%2][t-bino[N][n]]) % MOD;
        }
    }

    cout << DP[N%2][T];
}