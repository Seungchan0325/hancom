#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll cache[30][100][100];

ll dp(ll n, ll x, ll y)
{
    if(x < 0 || x >= 100 || y < 0 || y >= 100) return 0;
    if(n == 0) {
        if(x == 50 && y == 50) return 1;
        else return 0;
    }

    ll& ret = cache[n][x][y];
    if(ret != -1) return ret;

    ret = dp(n-1, x-1, y-1);
    ret += dp(n-1, x-1, y+1);
    ret += dp(n-1, x+1, y+1);
    ret += dp(n-1, x+1, y-1);
    ret += dp(n-1, x-2, y);
    ret += dp(n-1, x+2, y);
    return ret;
}

int main()
{
    ll n;
    cin >> n;

    memset(cache, -1, sizeof(cache));
    ll result = dp(n, 50, 50);
    cout << result;
}