#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int MAXM = 25;

int N, M;
string ring, ab[2];
int cache[2][MAXN][MAXM];

int dp(int up, int i, int j)
{
    if(j == M+1) return 1;
    int& ret = cache[up][i][j];
    if(ret != -1) return ret;

    ret = 0;
    for(int nxt = i + 1; nxt <= N; nxt++) {
        if(ring[j] == ab[1-up][nxt]) {
            ret += dp(1 - up, nxt, j + 1);
        }
    }

    return ret;
}

int main()
{
    cin >> ring;
    M = ring.size();
    cin >> ab[0] >> ab[1];
    N = ab[0].size();
    ring = " " + ring;
    ab[0] = ' ' + ab[0];
    ab[1] = ' ' + ab[1];

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0, 1) + dp(1, 0, 1);
    cout << result;
}