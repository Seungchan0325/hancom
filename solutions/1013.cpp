#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5;
const int MAXM = 10;

int N, M, ans = 100;
int t[MAXN][MAXM];
int canvas[MAXN][MAXM];

bool draw_r(int x, int y, int delta)
{
    if(x + 5 > M) return false;

    for(int j = x; j < x + 5; j++) {
        if((bool)t[y][j] == false) return false;
        canvas[y][j] += delta;
    }

    return true;
}

bool draw_u(int x, int y, int delta)
{
    if(y + 5 > N) return false;

    for(int j = y; j < y + 5; j++) {
        if((bool)t[j][x] == false) return false;
        canvas[j][x] += delta;
    }

    return true;
}

void f(int dep)
{
    if(dep >= ans) return;

    int x = -1, y = -1;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if((bool)t[i][j] != (bool)canvas[i][j]) {
                y = i;
                x = j;
                goto escape;
            }
        }
    }

    if(x == -1) {
        ans = dep;
        return;
    }

escape:

    if(draw_u(x, 0, 1)) f(dep+1);
    draw_u(x, 0, -1);

    bool b = false;
    for(int i = x; i >= max(0, x - 5); i--) {
        if(draw_r(i, y, 1)) {
            f(dep+1);
            b = true;
        }
        draw_r(i, y, -1);

        if(b) break;
    }
}

int main()
{
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            char c;
            cin >> c;
            if(c == '*') t[i][j]++;
        }
    }

    f(0);

    if(ans >= 100) cout << -1;
    else cout << ans;
}