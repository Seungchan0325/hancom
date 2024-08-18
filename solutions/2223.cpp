#include <bits/stdc++.h>

using namespace std;

const int INF = 1e8;

int N, M, B, dist[505];
vector<int> graph[505];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;
    while(tc--) {
        cin >> N >> M >> B;
        for(int i = 0; i <= N; i++) {
            dist[i] = 0;
            graph[i].clear();
        }
        vector<tuple<int, int, int>> edges;
        for(int i = 0; i < M; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back(v);
            graph[v].push_back(u);
            edges.emplace_back(u, v, w);
            edges.emplace_back(v, u, w);
        }

        for(int i = 0; i < B; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back(v);
            edges.emplace_back(u, v, -w);
        }

        for(int i = 0; i < N; i++) {
            for(auto [u, v, w] : edges) {
                if(dist[u] == INF) continue;
                if(dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        bool ispossible = false;
        for(auto [u, v, w] : edges) {
            if(dist[u] == INF) continue;
            if(dist[v] > dist[u] + w) {
                ispossible = true;
                break;
            }
        }

        if(ispossible) cout << "YES\n";
        else cout << "NO\n";
    }
}