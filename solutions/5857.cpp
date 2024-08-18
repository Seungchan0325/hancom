#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 3005;

ll N, K, A[MAXN], DP[MAXN][MAXN];

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for(int n = 1; n <= N; n++) {
        DP[n][0] = max(DP[n-1][K-1] + A[n], DP[n-1][0]);
        for(int k = 1; k < K; k++) {
            DP[n][k] = DP[n-1][max(k-1,0)];
            DP[n][k] = max(DP[n][k], DP[max(n-k, 0)][K-k] + A[n]);
        }
    }

    ll mx = 0;
    for(int k = 0; k <= K; k++) {
        mx = max(mx, DP[N][k]);
    }

    cout << mx;
}