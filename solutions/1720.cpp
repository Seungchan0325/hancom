#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

bool chk[MAXN];
int N, M, H[MAXN], root[MAXN], dist[MAXN];
vector<pair<int, int>> graph[MAXN];

int find(int u)
{
    if(root[u] == u) return u;
    return root[u] = find(root[u]);
}

void merge(int u, int v)
{
    u = find(u);
    v = find(v);
    root[v] = u;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> H[i];
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    vector<pair<int, int>> v;
    for(int i = 1; i <= N; i++) v.emplace_back(H[i], i);
    sort(v.begin(), v.end());

    int mn = 1e9;
    int lo = -1, hi = -1;
    for(int i = 0; i < v.size(); i++) {
        iota(root, root + N + 1, 0);
        for(int j = i; j < v.size(); j++) {
            for(auto [k, w] : graph[v[j].second])
                if(v[i].first <= H[k] && H[k] <= v[j].first)
                    merge(v[j].second, k);

            if(find(1) == find(N)) {
                if(v[j].first - v[i].first < mn) {
                    mn = v[j].first - v[i].first;
                    lo = v[i].first;
                    hi = v[j].first;
                }
                break;
            }
        }
    }

    memset(dist, 0x7F, sizeof(dist));
    dist[1] = 0;
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, 1);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;

        if(dist[u] < d) continue;

        for(auto [v, w] : graph[u]) {
            if(H[v] < lo || hi < H[v]) continue;
            int nd = d + w;
            if(nd < dist[v]) {
                pq.emplace(-nd, v);
                dist[v] = nd;
            }
        }
    }

    cout << mn << " " << dist[N];
}