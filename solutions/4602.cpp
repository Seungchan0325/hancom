#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 300005;

int N, sz[MAXN];
ll ans;
vector<int> graph[MAXN];

void dfs(int u, int p, int dep)
{
    sz[u] = 1;
    for(auto v : graph[u]) {
        if(v == p) continue;
        dfs(v, u, dep+1); sz[u] += sz[v];
    }

    ans += (ll)(N-sz[u])*(sz[u]);
    if(p != -1) ans += (ll)sz[u]*(sz[u]-1)/2;
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, -1, 0);
    cout << ans;
}