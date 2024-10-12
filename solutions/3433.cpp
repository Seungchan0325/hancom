#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXM = 100005;

int N, M, A[MAXM], B[MAXM], h[MAXM], lmn[MAXM], rmn[MAXM];

void fill(int l, int r)
{
    for(int i = l-1; i <= r+1; i++) lmn[i] = rmn[i] = 1e9;
    for(int i = l; i <= r; i++) {
        if(B[i] == N) lmn[i] = rmn[i] = A[i];
    }

    for(int i = l+1; i <= r; i++) {
        lmn[i] = min(lmn[i-1], lmn[i]);
    }
    for(int i = r-1; i >= l; i--) {
        rmn[i] = min(rmn[i+1], rmn[i]);
    }

    for(int i = l; i <= r; i++) {
        h[i] = max(lmn[i], rmn[i]);
    }
}

signed main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        cin >> A[i] >> B[i];
        assert(A[i] <= B[i] && B[i] <= N);
    }
    for(int i = 0; i <= M+1; i++) h[i] = 1e9;

    fill(1, M);
    
    long long ans = 0;
    for(int i = 1; i <= M; i++) {
        if(B[i] >= h[i]) {
            int t = max(A[i], h[i]);
            ans += N - h[i] + 1 - (B[i] - t + 1);
        } else {
            ans += max(N - h[i] + 1, 0LL);
        }
    }

    for(int i = 1; i <= M; i++) {
        if(B[i] == N || B[i] == 0) continue;
        int r = i;
        A[i] = min(A[i], h[i]);
        B[i] = N;
        while(r < M && B[r+1] != N && B[r+1] != 0) {
            r++;
            A[r] = min(A[r], h[r]);
            B[r] = N;
        }
        fill(i, r);
        for(int j = i; j <= r; j++) {
            int t = max(A[j], h[j]);
            ans += N - h[j] + 1 - (B[j] - t + 1);
        }
        i = r + 1;
    }
    cout << ans;
}