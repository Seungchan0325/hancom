#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

int N, D[MAXN], S[MAXN], P[MAXN], cache[MAXN][MAXN][2];

int dp(int i, int j, int cur)
{
    if(i < j) return dp(j, i, 1-cur);
    int& ret = cache[i][j][cur];
    if(ret != -1) return ret;

    ret = 0;
    for(int k = i+1; k < N; k++) {
        if(cur == 0) {
            if(D[k]-D[j] <= S[k] && P[k]) {
                ret += dp(k, i, 1-cur);
            }
            if(D[k]-D[i] <= S[i]) {
                ret += dp(k, j, cur);
            }
        } else {
            if(D[k]-D[j] <= S[j]) {
                ret += dp(k, i, 1-cur);
            }
            if(D[k]-D[i] <= S[k] && P[k]) {
                ret += dp(k, j, cur);
            }
        }
    }
    if(cur == 0) {
        if(D[N]-D[j] <= S[N] && D[N]-D[i] <= S[i]) {
            ret += dp(N, i, 1-cur);
        }
    } else {    
        if(D[N]-D[j] <= S[j] && D[N]-D[i] <= S[N]) {
            ret += dp(N, i, 1-cur);
        }
    }
    ret %= 1000;
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> D[i] >> S[i] >> P[i];
    }

    memset(cache, -1, sizeof(cache));
    for(int i = 0; i <= N; i++) {
        if(D[N] - D[i] <= S[i]) {
            cache[N][i][1] = 1;
        } else {
            cache[N][i][1] = 0;
        }
        if(P[i] && D[N] - D[i] < S[N]) {
            cache[N][i][0] = 1;
        } else {
            cache[N][i][0] = 0;
        }
    }
    int result = dp(1, 1, 0);
    cout << result;
}