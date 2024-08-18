#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int N, M, A[MAXN][MAXN];

int bfs(int x, int y)
{
    int dep = 0;
    queue<pair<int, int>> q;
    bool visited[MAXN][MAXN] = {};

    q.emplace(y, x);
    visited[y][x] = true;

    while(!q.empty()) {
        int sz = q.size();
        queue<pair<int, int>> tmp = q;
        q = queue<pair<int, int>>();

        while(!tmp.empty()) {
            auto [y, x] = tmp.front(); tmp.pop();

            for(int i = 0; i < 4; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];

                if(ny < 0 || ny >= N || nx < 0 || nx >= M || visited[ny][nx]) continue;

                visited[ny][nx] = true;
                if(A[ny][nx] != A[y][x]) q.emplace(ny, nx);
                else tmp.emplace(ny, nx);
            }
        }

        dep++;
    }

    return dep - 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> A[i][j];
        }
    }


    int ans = 1e8;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(j > 0 && A[i][j] == A[i][j-1]) continue;
            if(i > 0 && A[i][j] == A[i-1][j]) continue;
            ans = min(ans, bfs(j, i));
        }
    }

    cout << ans;
}