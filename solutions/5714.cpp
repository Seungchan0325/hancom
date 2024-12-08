#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

int ans;
int N, sz[MAXN], dp1[MAXN], dp2[MAXN];
vector<int> graph[MAXN];

void dfs(int u, int p)
{
    dp1[u] = 0;
    dp2[u] = 0;
    int f = -1e9;
    int s = -1e9;
    for(auto v : graph[u]) {
        if(v == p) continue;
        dfs(v, u);
        dp1[u] = max(dp1[u], dp1[v] + 1);
        dp2[u] = max(dp2[u], dp2[v]);

        if(dp1[v] + 1 > f) {
            s = f;
            f = dp1[v] + 1;
        } else if(dp1[v] + 1 > s) {
            s = dp1[v] + 1;
        }
    }

    dp2[u] = max(dp2[u], f + s);
}

void dfs2(int u, int p, int pdp1, int pdp2){
    vector<pair<int, int>> a, b;
    if(p != -1) {
        a.emplace_back(pdp1 + 1, p);
        b.emplace_back(pdp2, p);
    }
    for(auto v : graph[u]) {
        if(v == p) continue;
        a.emplace_back(dp1[v] + 1, v);
        b.emplace_back(dp2[v], v);
    }
    sort(a.begin(), a.end(), greater<>());

    for(auto [vdp2, v] : b) {
        if(a.size() >= 3) {
            if(a[0].second == v) {
                ans = max(ans, a[1].first + a[2].first + vdp2 + 1);
            } else if(a[1].second == v) {
                ans = max(ans, a[0].first + a[2].first + vdp2 + 1);
            } else {
                ans = max(ans, a[0].first + a[1].first + vdp2 + 1);
            }
        }

        if(a.size() >= 2) {
            if(a[0].second == v) {
                ans = max(ans, a[1].first + vdp2 + 1);
            } else {
                ans = max(ans, a[0].first + vdp2 + 1);
            }
        }

        ans = max(ans, vdp2);
        ans = max(ans, a[0].first);
    }

    for(auto v : graph[u]) {
        if(v == p) continue;
        int npdp1 = pdp1;
        if(a.size() >= 2) {
            if(a[0].second == v) {
                npdp1 = max(npdp1, a[1].first);
            } else {
                npdp1 = max(npdp1, a[0].first);
            }
        }
        if(a.size() >= 1) {
            if(a[0].second != v) {
                npdp1 = max(npdp1, a[0].first);
            }
        }
        int npdp2 = pdp2;
        if(a.size() >= 3) {
            if(a[0].second == v) {
                npdp2 = max(npdp2, a[1].first + a[2].first);
            } else if(a[1].second == v) {
                npdp2 = max(npdp2, a[0].first + a[2].first);
            } else {
                npdp2 = max(npdp2, a[0].first + a[1].first);
            }
        }
        if(a.size() >= 2) {
            if(a[0].second != v && a[1].second != v) {
                npdp2 = max(npdp2, a[0].first + a[1].first);
            }
        }
        dfs2(v, u, npdp1, npdp2);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, -1);
    dfs2(1, -1, 0, 0);

    cout << ans;
}