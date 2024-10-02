#include <bits/stdc++.h>

using namespace std;

const int MAXL = 55;
const int INF = 98654321;

int cache[MAXL][MAXL][MAXL][MAXL];

int dp(int h1, int w1, int h2, int w2)
{
    if(h2 == 0 || w2 == 0) h2 = w2 = 0;
    if(h2 == 0 && w2 == 0 && h1 == w1) return 1;
    int& ret = cache[h1][w1][h2][w2];
    if(ret != -1) return ret;

    ret = INF;
    for(int i = 1; i <= h2; i++) {
        ret = min(ret, dp(i, w1 - w2, 0, 0) + dp(h1 - i, w1, h2 - i, w2));
    }
    for(int i = 1; i <= w2; i++) {
        ret = min(ret, dp(h1 - h2, i, 0, 0) + dp(h1, w1 - i, h2, w2 - i));
    }
    for(int i = h2+1; i < h1; i++) {
        ret = min(ret, dp(i, w1, h2, w2) + dp(h1 - i, w1, 0, 0));
    }
    for(int i = w2+1; i < w1; i++) {
        ret = min(ret, dp(h1, i, h2, w2) + dp(h1, w1 - i, 0, 0));
    }
    return ret;
}

int main()
{
    int h1, w1, h2, w2;
    cin >> h1 >> w1 >> h2 >> w2;
    memset(cache, -1, sizeof(cache));
    int result = dp(h1, w1, h2, w2);
    cout << result;
}