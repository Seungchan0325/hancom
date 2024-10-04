#include <bits/stdc++.h>

using namespace std;

const int M = 10000;
const int INF = 1e9;

const int MAXN = 3005;

int N, T, H, A[MAXN], sum[MAXN], DP[MAXN];

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int mx = 0;

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    cin >> T >> H;
    
    sort(A+1, A+N+1);

    for(int i = 1; i <= N; i++) {
        sum[i] += sum[i-1] + A[i];
    }

    for(int i = 1; i <= N; i++) {
        DP[i] = T * (sum[i] - sum[0]);
        for(int j = 1; j <= i; j++) {
            int k = (i + j) / 2;
            int l = A[k] * (k - j + 1) - (sum[k] - sum[j-1]);
            int r = (sum[i] - sum[k-1]) - A[k] * (i - k + 1);
            int cost = H + T * (l + r);

            DP[i] = min(DP[i], DP[j-1] + cost);
        }
    }

    cout << DP[N];
}