#include <bits/stdc++.h>

using namespace std;

const int MAXN = 22;

int s;
int N, A[MAXN][MAXN], cache[40005][MAXN][MAXN];

int dp(int ps, int i, int prv)
{
    if(i == N+1) {
        return abs(s - ps - ps);
    }
    int& ret = cache[ps][i][prv];
    if(ret != -1) return ret;
    
    ret = 1e9;
    for(int j = prv; j >= 0; j--) {
        int nps = ps + A[j][i];
        ret = min(dp(nps, i+1, j), ret);
    }

    return ret;
}

void restruct(int ps, int i, int prv)
{
    if(i == N+1) {
        return;
    }
    
    for(int j = prv; j >= 0; j--) {
        int nps = ps + A[j][i];
        if(dp(nps, i+1, j) == dp(ps, i, prv)) {
            cout << N - j << " ";
            restruct(nps, i+1, j);
            return;
        }
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> A[i][j];
            s += A[i][j];
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            A[i][j] += A[i-1][j];
        }
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 1, N);
    cout << result << "\n";
    restruct(0, 1, N);
}