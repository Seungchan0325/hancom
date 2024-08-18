#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int INF = 1e8;

int N, cache[MAXN][MAXN][MAXN];
string s;

int dp(int l, int r, int h)
{
    if(l == r + 1) return 0;
    if(r < l || h == 0) return INF;
    int& ret = cache[l][r][h];
    if(ret != -1) return ret;

    ret = dp(l, r, h-1);
    for(int i = l+1; i <= r; i+=2) {
        if(s[l] != s[i]) {
            for(int nh = 1; nh <= h; nh++) {
                ret = min(ret, 2 * nh + i - l + dp(l+1, i-1, nh-1) + dp(i+1, r, h));
            }
        }
    }

    return ret;
}

void restruct(int l, int r, int h)
{
    if(l == r + 1) return;
    if(r < l || h == 0) return;

    if(dp(l, r, h) == dp(l, r, h-1)) {
        restruct(l, r, h-1);
        return;
    }
    for(int i = l+1; i <= r; i+=2) {
        if(s[l] != s[i]) {
            for(int nh = 1; nh <= h; nh++) {
                if(dp(l, r, h) == 2 * nh + i - l + dp(l+1, i-1, nh-1) + dp(i+1, r, h)) {
                    cout << l << " " << i << "\n";
                    restruct(l+1, i-1, nh-1);
                    restruct(i+1, r, h);
                    return;
                }
            }
        }
    }
}

int main()
{
    cin >> N;
    cin >> s;

    s = ' ' + s;

    memset(cache, -1, sizeof(cache));
    int result = dp(1, N, N);

    cout << result << "\n";

    restruct(1, N, N);
}