#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 35;

ll DP[MAXN][MAXN];

void generate(ll n, ll l, ll k)
{
    if(n == l) {
        for(ll i = n-1; i >= 0; i--) {
            if(k & (1<<i)) cout << "1";
            else cout << "0";
        }
        return;
    }
    if(n == 0) return;

    if(k < DP[n-1][l]) {
        cout << "0";
        generate(n-1, l, k);
    } else {
        cout << "1";
        generate(n-1, l-1, k - DP[n-1][l]);
    }
}

int main()
{
    DP[0][0] = 1;
    for(ll n = 1; n < MAXN; n++) {
        DP[n][0] = 1;
        DP[n][n] = 2*DP[n-1][n-1];
        for(ll l = 1; l < n; l++) {
            DP[n][l] = DP[n-1][l] + DP[n-1][l-1];
        }
    }

    ll N, L, K;
    cin >> N >> L >> K;
    generate(N, L, K-1);
}