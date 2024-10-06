#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int N, DP[MAXN][2];
vector<int> graph[MAXN];

void dfs(int u, int p)
{
    DP[u][0] = 1;
    for(auto v : graph[u]) {
        if(v == p) continue;
        dfs(v, u);
        DP[u][0] += min(DP[v][0], DP[v][1]);
        DP[u][1] += DP[v][0];
    }
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

    dfs(1, -1);
    cout << min(DP[1][0], DP[1][1]);
}