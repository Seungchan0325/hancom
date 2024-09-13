#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;
const int MAXX = 205;

int N, M, X, D[MAXN][MAXX][3], T[MAXN];
vector<pair<int, int>> graph[MAXN];

int main()
{
    cin >> N >> M >> X;
    for(int i = 1; i <= N; i++) {
        cin >> T[i];
    }

    for(int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    memset(D, 0x7F, sizeof(D));

    priority_queue<tuple<int, int, int, int>> pq;
    pq.emplace(0, 1, T[1], 0);

    int ans = 1e8;

    while(!pq.empty()) {
        auto [d, u, c, t] = pq.top(); pq.pop();
        d = -d;
        if(d > D[u][t][c]) continue;

        if(u == N) {
            ans = min(ans, d);
        }

        for(auto [v, w] : graph[u]) {
            int nd = d + w;
            int nt = min(t + w, X);
            int nc = c;
            if(T[v] != 1) nc = T[v];

            if(T[v] == 1) {
                if(nd < D[v][nt][nc]) {
                    pq.emplace(-nd, v, nc, nt);
                    D[v][nt][nc] = nd;
                }
            } else {
                if(c != T[v] && nt < X) continue;

                if(nd < D[v][nt][nc]) {
                    pq.emplace(-nd, v, nc, 0);
                    D[v][nt][nc] = nd;
                }
            }
        }
    }

    cout << ans;
}