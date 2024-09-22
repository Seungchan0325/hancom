#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

bool ans[MAXN];
int N, M, low[MAXN], num[MAXN], pv;
vector<int> graph[MAXN];

void dfs(int u, int p)
{
    num[u] = low[u] = ++pv;

    for(auto v : graph[u]) {
        if(!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= num[u]) ans[u] = true;
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int u = 1; u <= N; u++) {
        if(num[u]) continue;

        num[u] = low[u] = ++pv;
        int cnt = 0;
        for(auto v : graph[u]) {
            if(!num[v]) {
                dfs(v, u);
                cnt++;
            }
        }

        if(cnt >= 2) ans[u] = true;
    }

    bool flag = true;
    for(int i = 1; i <= N; i++) {
        if(ans[i]) {
            cout << i << " ";
            flag = false;
        }
    }
    if(flag) cout << "-1\n";
}