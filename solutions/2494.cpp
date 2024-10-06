#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int s[MAXN], e[MAXN];
int N, cache[MAXN][11];

int dp(int idx, int left)
{
    if(idx == N+1) return 0;
    int& ret = cache[idx][left];
    if(ret != -1) return ret;

    ret = 1e9;

    int cur = (s[idx] + left) % 10;

    int lt = (e[idx] + 10 - cur) % 10;
    ret = min(ret, dp(idx+1, (left + lt) % 10) + lt);
    int rt = (cur - e[idx] + 10) % 10;
    ret = min(ret, dp(idx+1, left) + rt);

    return ret;
}

void restruct(int idx, int left)
{
    if(idx == N+1) return;

    int cur = (s[idx] + left) % 10;

    int lt = (e[idx] + 10 - cur) % 10;
    if(dp(idx+1, (left + lt) % 10) + lt == dp(idx, left)) {
        cout << idx << " " << lt << "\n";
        restruct(idx+1, (left + lt) % 10);
        return;
    }
    int rt = (cur - e[idx] + 10) % 10;
    if(dp(idx+1, left) + rt == dp(idx, left)) {
        cout << idx << " " << -rt << "\n";
        restruct(idx+1, left);
        return;
    }
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        char c;
        cin >> c;
        s[i+1] = c - '0';
    }
    for(int i = 0; i < N; i++) {
        char c;
        cin >> c;
        e[i+1] = c - '0';
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(1, 0);
    cout << result << "\n";
    restruct(1, 0);
}