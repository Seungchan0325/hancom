#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int N, M, outDeg[MAXN];
vector<int> graph[MAXN];

bool inStack[MAXN];
int low[MAXN], num[MAXN], scc[MAXN], pv, t;
stack<int> s;

void dfs(int u)
{
    low[u] = num[u] = ++pv;
    inStack[u] = true;
    s.push(u);

    for(auto v : graph[u]) {
        if(!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if(num[u] == low[u]) {
        t++;
        while(s.top() != u) {
            scc[s.top()] = t;
            inStack[s.top()] = false;
            s.pop();
        }

        scc[u] = t;
        inStack[u] = false;
        s.pop();
    }
}

int main()
{
    cin >> N >> M;
    vector<pair<int, int>> edges;
    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        edges.emplace_back(u, v);
    }

    for(int i = 1; i <= N; i++) {
        if(!num[i]) dfs(i);
    }

    for(auto [u, v] : edges) {
        if(scc[u] == scc[v]) continue;
        outDeg[scc[u]]++;
    }

    int cnt = 0;
    int _scc = -1;
    int ans = 0;

    for(int i = 1; i <= t; i++) {
        if(outDeg[i] == 0) {
            _scc = i;
            cnt++;
        }
    }

    for(int i = 1; i <= N; i++) {
        if(scc[i] == _scc) ans++;
    }

    if(cnt >= 2) cout << "0";
    else cout << ans;
}