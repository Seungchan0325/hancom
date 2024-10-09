#include <bits/stdc++.h>

using namespace std;

int cache[1000001];

int solve(int a, int b)
{
    if(a == 0 && b <= 1e6 && cache[b]) return cache[b];
    if(b < a) return -1e9;
    if(a == 0 && b == 1) return 1;
    if(a == 0 && b == 0) return 0;
    int k = 31 - __builtin_clz(b+1);
    int v = (1<<k)-1;
    if(v < a) return k + solve(a - v, b - v);

    int ret = max(solve(a, v-1), k + solve(0, b - v));
    if(a == 0 && b <= 1e6) cache[b] = ret;
    return ret;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int x, y;
        cin >> x >> y;

        int ans = solve(x, y);
        cout << ans << "\n";
    }
}