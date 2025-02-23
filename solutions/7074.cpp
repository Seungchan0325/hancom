#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50505;

bool vst[MAXN];
bitset<MAXN> from[MAXN];
int N, M, mn[MAXN], mx[MAXN], A[MAXN], d[MAXN];
vector<int> g[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    vector<pair<int, int>> start;
    for(int i = 1; i <= N; i++) {
        d[i] = 1e9;
        if(A[i] != -1) start.emplace_back(-A[i], i);
    }
    sort(start.begin(), start.end());

    int idx = 0;
    queue<int> q;
    for(int t = -N; t < 0; t++) {
        while(idx < start.size() && start[idx].first <= t) {
            int u = start[idx].second;
            if(d[u] >= t) {
                from[u].set(u);
            }
            if(!vst[u]) {
                vst[u] = true;
                d[u] = t;
                q.push(u);
            }
            idx++;
        }

        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            auto u = q.front(); q.pop();
            for(auto v : g[u]) {
                if(d[v] >= t+1) from[v] |= from[u];
                if(vst[v]) continue;
                vst[v] = true;
                d[v] = t + 1;
                q.push(v);
            }
        }
    }
    
    while(idx < start.size() && start[idx].first <= 0) {
        int u = start[idx].second;
        if(d[u] >= 0) {
            from[u].set(u);
        }
        if(!vst[u]) {
            vst[u] = true;
            d[u] = 0;
            q.push(u);
        }
        idx++;
    }

    vector<int> ans;
    for(int i = 1; i <= N; i++) {
        if(d[i] >= 0 && from[i].count() == start.size()) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << "\n";
    for(int i : ans) cout << i << " ";
}