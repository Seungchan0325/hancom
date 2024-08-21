#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, p[MAXN], in[MAXN], out[MAXN], pv = -1, tree[2*MAXN], ans[MAXN];
vector<int> graph[MAXN];

void dfs(int u)
{
    in[u] = ++pv;
    for(auto v : graph[u]) {
        dfs(v);
    }
    out[u] = pv;
}

void update(int x, int v)
{
    for(tree[x+=N] += v; x > 1; x >>= 1) {
        tree[x>>1] = tree[x] + tree[x^1];
    }
}

int query(int l, int r)
{
    int ret = 0;
    for(l+=N, r+=N; l <= r; l>>=1, r>>=1) {
        if(l&1) ret += tree[l++];
        if(~r&1) ret += tree[r--];
    }
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> p[i];
    }
    for(int i = 2; i <= N; i++) {
        int par;
        cin >> par;
        graph[par].push_back(i);
    }

    dfs(1);

    vector<pair<int, int>> v;
    for(int i = 1; i <= N; i++) {
        v.emplace_back(p[i], i);
    }
    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b){
        if(a.first != b.first) return a.first > b.first;
        return in[a.second] < in[b.second];
    });

    for(auto [pi, u] : v) {
        ans[u] = query(in[u], out[u]);
        update(in[u], 1);
    }
    
    for(int i = 1; i <= N; i++) {
        cout << ans[i] << "\n";
    }
}