#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 300005;

bool chk[MAXN], has_cycle[MAXN], has_bridge[MAXN];
long long N, M, pv, num[MAXN], par[MAXN];
vector<long long> graph[MAXN], g[MAXN], gg[MAXN], backedges[MAXN];
multiset<long long> pq[MAXN];

void dfs(long long u)
{
    num[u] = ++pv;

    for(auto v : graph[u]) {
        if(!num[v]) {
            par[v] = u;
            dfs(v);
            g[u].push_back(v);

            if(has_cycle[v]) has_cycle[u] = true;

            bool f = has_cycle[v];
            if(pq[v].count(num[u])) {
                pq[v].erase(num[u]);
                has_cycle[u] = true;
                f = true;
            }
            if(pq[v].size()) f = true;
            gg[u].push_back(f);
            if(pq[v].size() >= 2) has_bridge[u] = true;

            if(pq[u].size() < pq[v].size()) swap(pq[u], pq[v]);
            pq[u].insert(pq[v].begin(), pq[v].end());
        } else if(par[u] != v && num[v] < num[u]) {
            backedges[u].push_back(v);
            pq[u].insert(num[v]);
        }
    }
}

long long dfs2(long long u, bool pcycle)
{
    long long ret = 0;
    bool sub_cycle = false;

    long long cnt = 0;
    for(long long i = 0; i < g[u].size(); i++) {
        if(gg[u][i]) cnt++;
    }
    for(long long i = 0; i < g[u].size(); i++) {
        long long v = g[u][i];

        bool npcycle = pcycle;
        if(backedges[u].size()) npcycle = true;
        if(gg[u][i]) cnt--;
        if(cnt) npcycle = true;
        if(gg[u][i]) cnt++;

        ret += dfs2(v, npcycle);
        sub_cycle |= has_cycle[v];
    }

    if(!pcycle && !sub_cycle && !has_bridge[u]) {
        ret += u;
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(long long i = 1; i <= M; i++) {
        long long u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    long long ans = 0;

    dfs(1);
    ans += dfs2(1, false);

    cout << ans;
}