#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

int N, L, nd, indeg[3*MAXN], sindeg[MAXN], r[3*MAXN];
ll dp[3*MAXN];
vector<pair<int, int>> nds[2][MAXN];
vector<int> graph[3*MAXN];

signed main()
{
    cin >> N >> L;
    vector<pair<int, int>> v(N);
    vector<int> ts, ds;
    for(auto& [t, d] : v) {
        cin >> t >> d;
        ts.push_back(t);
        ds.push_back(d);
    }

    sort(ts.begin(), ts.end());
    ts.erase(unique(ts.begin(), ts.end()), ts.end());
    sort(ds.begin(), ds.end());
    ds.erase(unique(ds.begin(), ds.end()), ds.end());

    vector<pair<int, int>> vv(N);
    vector<ll> c(N);
    for(int i = 0; i < N; i++) {
        auto [t, d] = v[i];
        c[i] = abs(t - d) + L;
        t = lower_bound(ts.begin(), ts.end(), t) - ts.begin();
        d = lower_bound(ds.begin(), ds.end(), d) - ds.begin();
        nds[0][t].emplace_back(d, i);
        nds[1][d].emplace_back(t, i);
    }

    for(int i = 0; i < ts.size(); i++) {
        sort(nds[0][i].begin(), nds[0][i].end());
        for(int j = 0; j < nds[0][i].size(); j++) {
            int idx = nds[0][i][j].second;
            r[nd+j] = idx;
            vv[idx].first = nd+j;
        }
        for(int j = 1; j < nds[0][i].size(); j++) {
            graph[nd+j-1].push_back(nd+j);
            indeg[nd+j]++;
        }
        nd += nds[0][i].size();
    }

    for(int i = 0; i < ds.size(); i++) {
        sort(nds[1][i].begin(), nds[1][i].end());
        for(int j = 0; j < nds[1][i].size(); j++) {
            int idx = nds[1][i][j].second;
            r[nd+j] = idx;
            vv[idx].second = nd+j;
        }
        for(int j = 1; j < nds[1][i].size(); j++) {
            graph[nd+j-1].push_back(nd+j);
            indeg[nd+j]++;
        }
        nd += nds[1][i].size();
    }

    queue<int> q;
    for(int i = 0; i < N; i++) {
        auto [a, b] = vv[i];
        sindeg[i] = indeg[a] + indeg[b];
        if(sindeg[i] == 0) {
            ll t = dp[a];
            dp[a] = max(dp[a], dp[b] + c[i]);
            dp[b] = max(dp[b], t + c[i]);
            q.push(a);
            q.push(b);
        }
    }

    ll mx = 0;
    while(!q.empty()) {
        auto u = q.front(); q.pop();
        mx = max(mx, dp[u]);
        for(auto v : graph[u]) {
            dp[v] = max(dp[v], dp[u]);

            if(--sindeg[r[v]] == 0) {
                auto [a, b] = vv[r[v]];

                ll t = dp[a];
                dp[a] = max(dp[a], dp[b] + c[r[v]]);
                dp[b] = max(dp[b], t + c[r[v]]);

                q.push(a);
                q.push(b);
            }

            // if(--indeg[v] == 0) {
            //     q.push(v);
            // }
        }
    }

    cout << mx;
}