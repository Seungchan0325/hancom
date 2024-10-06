#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, R, DP[MAXN];
vector<pair<int, int>> graph[MAXN];

void dfs(int u, int p)
{
    bool flag = true;
    for(auto [v, w] : graph[u]) {
        if(v == p) continue;
        flag = false;
        dfs(v, u);
        DP[u] += min(DP[v], w);
    }
    if(flag) DP[u] = 1e9;
}

int main()
{
    while(true) {
        cin >> N >> R;
        if(N == 0) break;
        for(int i = 0; i <= N; i++) graph[i].clear(), DP[i] = 0;
        for(int i = 1; i < N; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        if(N == 1) {
            cout << "0\n";
            continue;
        }

        dfs(R, -1);
        cout << DP[R] << "\n";
    }
}