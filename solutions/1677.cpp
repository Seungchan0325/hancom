#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, A[MAXN][MAXN], DP[MAXN][MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> A[i][j];
        }
    }

    for(int i = 1; i <= N; i++) {
        DP[1][i] = DP[1][i-1] + A[1][i];
    }

    for(int i = 2; i <= N; i++) {
        int mx = -1e8;
        for(int j = 1; j <= N; j++) {
            mx = max(mx, DP[i-1][j]);
            mx += A[i][j];
            DP[i][j] = mx;
        }

        mx = -1e8;
        for(int j = N; j >= 1; j--) {
            mx = max(mx, DP[i-1][j]);
            mx += A[i][j];
            DP[i][j] = max(DP[i][j], mx);
        }
    }

    cout << DP[N][N];
}