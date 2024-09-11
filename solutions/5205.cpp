#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

int N, M, DP[MAXN][MAXN], chk[MAXN];
vector<pair<int, int>> graph[MAXN];

void dfs(int u)
{
    chk[u] = true;
    if(graph[u].size() == 0) DP[u][u] = 1;
    for(auto [v, k] : graph[u]) {
        if(!chk[v]) dfs(v);
        for(int i = 1; i <= N; i++) {
            DP[u][i] += k * DP[v][i];
        }
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int X, Y, K;
        cin >> X >> Y >> K;
        graph[X].emplace_back(Y, K);
    }

    dfs(N);

    for(int i = 1; i <= N; i++) {
        if(DP[N][i]) {
            cout << i << " " << DP[N][i] << "\n";
        }
    }
}