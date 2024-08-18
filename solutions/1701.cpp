#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int INF = 1e8;

int N, cache[MAXN][MAXN], lst_t[MAXN], lst_c[MAXN];
string s;

int dp(int l, int r)
{
    if(r < l) return 0;
    int& ret = cache[l][r];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = l; i < r; i++) {
        if(s[i] == 'a') {
            int j = lst_t[r];
            if(j < i) continue;
            ret = max(ret, dp(l, i-1) + dp(i+1, j-1) + dp(j+1, r) + 2);
        }

        if(s[i] == 'g') {
            int j = lst_c[r];
            if(j < i) continue;
            ret = max(ret, dp(l, i-1) + dp(i+1, j-1) + dp(j+1, r) + 2);
        }
    }

    return ret;
}

int main()
{
    cin >> s;
    N = s.size();
    s = ' ' + s;

    memset(lst_t, -1, sizeof(lst_t));
    memset(lst_c, -1, sizeof(lst_c));
    for(int i = 1; i <= N; i++) {
        if(s[i] == 't') lst_t[i] = i;
        else lst_t[i] = lst_t[i-1];
        if(s[i] == 'c') lst_c[i] = i;
        else lst_c[i] = lst_c[i-1];
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(1, N);
    cout << result;
}