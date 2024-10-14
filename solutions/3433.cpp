#include <bits/stdc++.h>

using namespace std;

const int MAXM = 100005;

int N, M, A[MAXM], B[MAXM], h[2][MAXM], lmn[MAXM], rmn[MAXM];

void fill(int l, int r, bool ground)
{
    for(int i = l; i <= r; i++) lmn[i] = rmn[i] = N+1;
    for(int i = l; i <= r; i++) {
        if((!ground || B[i] >= N) && B[i] != 0) lmn[i] = rmn[i] = A[i];
    }

    for(int i = l+1; i <= r; i++) {
        lmn[i] = min(lmn[i-1], lmn[i]);
    }
    for(int i = r-1; i >= l; i--) {
        rmn[i] = min(rmn[i+1], rmn[i]);
    }


    for(int i = l; i <= r; i++) {
        h[ground][i] = max(lmn[i], rmn[i]);
    }
}

signed main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        cin >> A[i] >> B[i];
        // assert(A[i] <= B[i] && B[i] <= N);
    }

    for(int i = 0; i < 2; i++) for(int j = 1; j <= M; j++) h[i][j] = N+1;

    fill(1, M, true);
    
    for(int i = 1; i <= M; i++) {
        if(B[i] < N && B[i] != 0) {
            int r = i;
            while(r < M && B[r+1] != 0 && A[r] <= B[r+1] && A[r+1] <= B[r]) {
                r++;
            }
            fill(i, r, false);
            i = r;
        }
    }

    long long ans = 0;
    for(int i = 1; i <= M; i++) {
        if(B[i] >= N) {
            ans += A[i] - h[1][i];
        } else if(B[i] == 0) {
            ans += N - h[1][i] + 1;
        }else {
            if(h[1][i] <= h[0][i]) {
                ans += N - h[1][i] + 1 - (B[i] - A[i] + 1);
            }
            else {
                ans += A[i] - h[0][i];
                ans += N - max(h[1][i], B[i]+1) + 1;
            }
        }
    }

    cout << ans;
}