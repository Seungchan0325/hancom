#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 25;

ll N, L, R, fac[MAXN], DP[MAXN][MAXN], nCr[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    nCr[0][0] = 1;
    for(int n = 1; n < MAXN; n++) {
        nCr[n][0] = 1;
        for(int r = 1; r < MAXN; r++) {
            nCr[n][r] = nCr[n-1][r] + nCr[n-1][r-1];
        }
    }

    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) fac[i] = fac[i-1] * i;

    DP[0][0] = 1;
    for(int n = 1; n < MAXN; n++) {
        for(int l = 1; l < MAXN; l++) {
            for(int i = 0; i < n; i++) {
                DP[n][l] += DP[n-i-1][l-1] * fac[i] * nCr[n-1][i];
            }
        }
    }

    ll tc;
    cin >> tc;
    while(tc--) {
        cin >> N >> L >> R;

        ll result = 0;
        for(int i = 0; i < N; i++) {
            result += nCr[N-1][i] * DP[i][R-1] * DP[N-i-1][L-1];
        }

        cout << result << "\n";
    }
}