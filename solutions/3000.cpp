#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const int LOGN = 18;

int N, Q, par[MAXN], sparse[MAXN][LOGN+1], dep[MAXN], in[MAXN], out[MAXN], pv, tree[4*MAXN], lazy[4*MAXN];
vector<int> graph[MAXN];

void dfs(int u)
{
    for(int i = 1; i <= LOGN; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    }

    in[u] = ++pv;
    for(auto v : graph[u]) {
        dep[v] = dep[u] + 1;
        sparse[v][0] = u;
        dfs(v);
    }
    out[u] = pv;
}

int LCA(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);

    int diff = dep[u] - dep[v];
    for(int i = 0; i <= LOGN; i++) {
        if(diff & (1<<i)) {
            u = sparse[u][i];
        }
    }

    if(u == v) return u;

    for(int i = LOGN; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }

    return sparse[u][0];
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] = max(lazy[idx], tree[idx]);
        if(s != e) {
            lazy[2*idx] = max(lazy[idx], lazy[2*idx]);
            lazy[2*idx+1] = max(lazy[idx], lazy[2*idx+1]);
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return;

    if(l <= s && e <= r) {
        lazy[idx] = v;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int x, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < x || x < s) return 0;

    if(s == e) return tree[idx];

    int m = (s + e) / 2;
    return max(query(x, s, m, 2*idx), query(x, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 2; i <= N; i++) {
        cin >> par[i];
        graph[par[i]].push_back(i);
    }

    dfs(1);

    while(Q--) {
        int b, c, d;
        cin >> b >> c >> d;

        if(d == 0) {
            int lca = LCA(b, c);
            int limit = max(query(in[b]), query(in[c]));
            if(dep[lca] >= limit) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else {
            int lca = LCA(c, b);
            int limit = max(query(in[b]), query(in[c]));
            if(dep[lca] >= limit) {
                update(in[b], out[b], dep[b]);
                cout << "YES\n";
            } else {
                update(in[c], out[c], dep[c]);
                cout << "NO\n";
            }
        }
    }
}