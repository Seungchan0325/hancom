#include <bits/stdc++.h>

using namespace std;

using tiii = tuple<int, int, int>;

const int MAXN = 505;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int N, M, T, wall[MAXN][MAXN];
vector<tuple<int, int, int, vector<vector<int>>>> LEDS;

vector<vector<int>> bfs(int sx, int sy)
{
    vector<vector<int>> dist(N+5, vector<int>(N+5, 1e9));
    queue<pair<int, int>> q;
    q.emplace(sx, sy);
    dist[sx][sy] = 0;

    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        for(int i = 0; i < 4; i++) {
            if(wall[x][y] & (1<<i)) continue;
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(ny < 1 || ny > N || nx < 1 || nx > N || dist[nx][ny] != 1e9) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.emplace(nx, ny);
        }
    }

    return dist;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> wall[i][j];
        }
    }
    cin >> M;
    vector<int> cs;
    for(int i = 0; i < M; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        LEDS.emplace_back(x, y, c, bfs(x, y));
        cs.push_back(c);
    }
    cin >> T;
    vector<int> s(T);
    for(auto& i : s) cin >> i;

    sort(cs.begin(), cs.end());
    cs.erase(unique(cs.begin(), cs.end()), cs.end());

    vector<vector<int>> m(cs.size());

    for(int i = 0; i < M; i++) {
        auto& [x, y, c, d] = LEDS[i];
        int idx = lower_bound(cs.begin(), cs.end(), c) - cs.begin();
        m[idx].push_back(i);
    }


    vector<tuple<int, int>> prv;

    auto sd = bfs(1, 1);
    int sidx = lower_bound(cs.begin(), cs.end(), s[0]) - cs.begin();
    for(int i = 0; i < m[sidx].size(); i++) {
        auto& [x, y, c, d] = LEDS[m[sidx][i]];
        prv.emplace_back(m[sidx][i], sd[x][y]);
    }

    for(int i = 1; i < T; i++) {
        int idx = lower_bound(cs.begin(), cs.end(), s[i]) - cs.begin();
        vector<int> D(m[idx].size(), 1e9);
        for(auto& [led, d] : prv) {
            auto& dd = get<3>(LEDS[led]);
            int j = 0;
            for(auto nled : m[idx]) {
                int x = get<0>(LEDS[nled]);
                int y = get<1>(LEDS[nled]);
                D[j] = min(D[j], d + dd[x][y]);
                j++;
            }
        }
        prv.clear();
        for(int j = 0; j < m[idx].size(); j++) {
            prv.emplace_back(m[idx][j], D[j]);
        }
    }

    int ans = 1e9;
    for(auto& [led, d] : prv) {
        auto& dd = get<3>(LEDS[led]);
        ans = min(d + dd[N][N], ans);
    }

    cout << ans + 2;
}