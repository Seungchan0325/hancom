#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;

int N, s[MAXN], K, cache[MAXN][3];

int dp(int n, int i)
{
    if(i == 3 || N < n) return 0;
    int& ret = cache[n][i];
    if(ret != -1) return ret;

    ret = dp(n+1, i);

    int nxt = min(n+K-1, N);
    int sum = s[nxt] - s[n-1];
    ret = max(ret, sum + dp(nxt+1, i+1));

    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> s[i];
        s[i] += s[i-1];
    }
    cin >> K;

    memset(cache, -1, sizeof(cache));
    int result = dp(1, 0);
    cout << result;
}