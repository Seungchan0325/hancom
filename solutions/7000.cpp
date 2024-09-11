#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int N, M, outDeg[MAXN], cost[MAXN], mn[MAXN];
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
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> cost[i];
    vector<pair<int, int>> edges;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            char c;
            cin >> c;
            if(c == '1') {
                graph[i].push_back(j);
                edges.emplace_back(i, j);
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        if(!num[i]) dfs(i);
    }

    for(int i = 1; i <= t; i++) {
        mn[i] = 1e9;
    }

    for(int i = 1; i <= N; i++) {
        mn[scc[i]] = min(mn[scc[i]], cost[i]);
    }

    int ans = 0;
    for(int i = 1; i <= t; i++) {
        ans += mn[i];
    }
    cout << ans;
}