#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};

int M, N, h[MAXN][MAXN], cache[MAXN][MAXN];

int dp(int r, int c)
{
    if(r < 0 || r > M || c < 0 || c > N) return 0;
    if(r == M && c == N) return 1;
    int& ret = cache[r][c];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(h[nr][nc] >= h[r][c]) continue;
        ret += dp(nr, nc);
    }

    return ret;
}

int main()
{
    cin >> M >> N;
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> h[i][j];
        }
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(1, 1);
    cout << result;
}