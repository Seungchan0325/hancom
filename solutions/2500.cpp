#include <bits/stdc++.h>

using namespace std;

const int MAXN = 205;
const int MAXK = 25;
const int INF = 1e8;

int N, K, A[MAXN], cache[MAXN][MAXN][MAXK];

int dp(int l, int r, int k)
{
    if(r < l) return 0;
    int& ret = cache[l][r][k];
    if(ret != -1) return ret;

    bool flag = true;
    for(int i = l; i < r; i++) if(A[i] != A[i+1]) flag = false;
    if(flag) {
        ret = k != A[l];
        return ret;
    }
    ret = INF;
    for(int i = l; i < r; i++) {
        ret = min(ret, dp(l, i, k) + dp(i+1, r, A[i+1]) + (k != A[i+1]));
        ret = min(ret, dp(l, i, k) + dp(i+1, r, A[r]) + (k != A[r]));
        ret = min(ret, dp(l, i, A[i]) + dp(i+1, r, k) + (k != A[i]));
        ret = min(ret, dp(l, i, A[l]) + dp(i+1, r, k) + (k != A[l]));
    }

    return ret;
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    memset(cache, -1, sizeof(cache));
    int result = INF;
    for(int k = 1; k <= K; k++) {
        result = min(result, dp(1, N, k));
    }
    cout << result;
}