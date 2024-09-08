#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, M, H, ver[MAXN][MAXN], hor[MAXN][MAXN], dist[MAXN*MAXN];
vector<pair<int, int>> graph[MAXN*MAXN];

int main()
{
    cin >> N >> M >> H;
    for(int i = 0; i < N+1; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> ver[i][j];
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < M+1; j++) {
            cin >> hor[i][j];
        }
    }

    for(int i = 0; i <= N+1; i++) {
        for(int j = 0; j <= M+1; j++) {
            dist[i*(M+2)+j] = H;
        }
    }

    for(int i = 0; i < N+1; i++) {
        for(int j = 1; j <= M; j++) {
            if(ver[i][j] != -1) {
                graph[i*(M+2)+j].emplace_back((i+1)*(M+2)+j, ver[i][j]);
                graph[(i+1)*(M+2)+j].emplace_back(i*(M+2)+j, ver[i][j]);
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < M+1; j++) {
            if(hor[i][j] != -1) {
                graph[i*(M+2)+j].emplace_back(i*(M+2)+j+1, hor[i][j]);
                graph[i*(M+2)+j+1].emplace_back(i*(M+2)+j, hor[i][j]);
            }
        }
    }

    priority_queue<pair<int, int>> pq;
    for(int i = 0; i <= N+1; i++) {
        // (i, 0)
        dist[i*(M+2)] = 0;
        pq.emplace(0, i*(M+2));
        // (i, M+1)
        dist[i*(M+2)+M+1] = 0;
        pq.emplace(0, i*(M+2)+M+1);
    }
    for(int i = 0; i <= M+1; i++) {
        // (0, i)
        dist[i] = 0;
        pq.emplace(0, i);
        // (N+1, i)
        dist[(N+1)*(M+2)+i] = 0;
        pq.emplace(0, (N+1)*(M+2)+i);
    }

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(dist[u] < d) continue;

        for(auto [v, w] : graph[u]) {
            int nd = max(d, w);
            if(nd < dist[v]) {
                pq.emplace(-nd, v);
                dist[v] = nd;
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            ans += dist[i*(M+2)+j];
        }
    }

    cout << ans;
}