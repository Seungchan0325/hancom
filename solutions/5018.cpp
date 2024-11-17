#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;

int N, P, Q, A[MAXN], L[MAXN], LL[MAXN], DP[MAXN][MAXN];

bool chk(int w)
{
    for(int i = 1; i <= N; i++) {
        L[i] = upper_bound(A+1, A+N+1, A[i]-w) - A - 1;
        LL[i] = upper_bound(A+1, A+N+1, A[i]-2*w) - A - 1;
    }

    for(int p = 0; p <= P; p++) DP[0][p] = 0;
    for(int i = 1; i <= N; i++) {
        DP[i][0] = DP[LL[i]][0] + 1;
        for(int p = 1; p <= P; p++) {
            DP[i][p] = min(DP[L[i]][p-1], DP[LL[i]][p] + 1);
        }
    }

    return DP[N][P] <= Q;
}

int main()
{
    cin >> N >> P >> Q;
    P = min(P, N);
    Q = min(Q, N);
    for(int i = 1; i <= N; i++) cin >> A[i];
    sort(A+1, A+N+1);

    int lo = 0;
    int hi = 1e9;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(chk(mid)) hi = mid;
        else lo = mid;
    }

    cout << hi;
}