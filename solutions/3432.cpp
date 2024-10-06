#include <bits/stdc++.h>

using namespace std;

using tiii = tuple<int, int, int>;

const int MAXN = 505;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

int N, M, T, wall[MAXN][MAXN];

vector<vector<int>> bfs(int sx, int sy)
{
    vector<vector<int>> dist(MAXN, vector<int>(MAXN, 1e9));
    queue<pair<int, int>> q;
    q.emplace(sy, sx);
    dist[sy][sx] = 0;

    while(!q.empty()) {
        auto [y, x] = q.front(); q.pop();

        for(int i = 0; i < N; i++) {
            if(wall[y][x] & (1<<i)) continue;
            int ny = y + dy[i];
            int nx = x + dx[i];
            if(ny < 1 || ny > N || nx < 1 || nx > N || dist[ny][nx] != 1e9) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.emplace(ny, nx);
        }
    }

    return dist;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> wall[i][j];
        }
    }
    cin >> M;
    vector<tuple<int, int, int>> v(M);
    vector<int> cs;
    for(auto& [x, y, c] : v) {
        cin >> x >> y >> c;
        cs.push_back(c);
    }
    cin >> T;
    vector<int> s(T);
    for(auto& i : s) cin >> i;

    sort(cs.begin(), cs.end());
    cs.erase(cs.begin(), cs.end());
}