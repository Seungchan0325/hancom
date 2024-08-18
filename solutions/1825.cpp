#include <bits/stdc++.h>

using namespace std;

const int MAXN = 25;
const int MAXP = 305;

int tot, N, c[MAXN][MAXP], cache[MAXN][MAXP];

int dp(int n, int t)
{
    if(t == 0 || n == N+1) return 0;
    int& ret = cache[n][t];
    if(ret != -1) return ret;

    ret = dp(n+1, t);
    for(int i = 1; i <= t; i++) {
        ret = max(ret, dp(n+1, t-i) + c[n][i]);
    }
    
    return ret;
}

void restruct(int n, int t)
{
    if(n == N+1) return;

    if(dp(n, t) == dp(n+1, t)) {
        cout << "0 ";
        restruct(n+1, t);
        return;
    }

    for(int i = 1; i <= t; i++) {
        if(dp(n, t) == dp(n+1, t-i) + c[n][i]) {
            cout << i << " ";
            restruct(n+1, t-i);
            return;
        }
    }
}

int main()
{
    cin >> tot >> N;
    for(int i = 1; i <= tot; i++) {
        int a;
        cin >> a;
        for(int j = 1; j <= N; j++) {
            cin >> c[j][i];
        }
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(1, tot);
    cout << result << "\n";
    restruct(1, tot);
}