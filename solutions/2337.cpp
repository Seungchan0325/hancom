#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int N, cost[MAXN], DP[2][MAXN];

int main()
{
    cin >> N;
    for(int i = 2; i <= N; i++) cin >> cost[i];

    memset(DP, 0x3F, sizeof(DP));
    // DP[1][1] = 987654321;
    for(int n = 2; n <= N; n++) {
        memset(DP[n%2], 0x3F, sizeof(DP[0]));
        for(int k = 1; k < n; k++) {
            DP[n%2][k] = min(DP[(n+1)%2][k], DP[(n+1)%2][n-1-k]+cost[n]);
        }
        DP[n%2][n-1] = min(DP[n%2][n-1], cost[n]);
    }

    cout << DP[N%2][N/2];
}