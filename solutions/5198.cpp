#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250005;

int N, Q, par[MAXN], root[MAXN], sz[MAXN];
vector<int> graph[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;

    root[y] = x;
    sz[x] += sz[y];
}

void dfs(int u, int p)
{
    par[u] = p;
    for(auto v : graph[u]) {
        if(v == p) continue;

        dfs(v, u);
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

    iota(root, root + N + 1, 0);
    fill(sz, sz + N + 1, 1);

    cin >> Q;

    while(Q--) {
        int k;
        cin >> k;
        vector<int> s(k);
        for(auto& i : s) cin >> i;
        sort(s.begin(), s.end());

        for(auto i : s) {
            if(binary_search(s.begin(), s.end(), par[i])) {
                merge(par[i], i);
            }
        }

        long long ans = 0;

        for(auto i : s) {
            if(find(i) == i) {
                int idx = find(i);
                ans += (long long)sz[idx] * (sz[idx] - 1) / 2;
            }
        }

        cout << ans << "\n";

        for(auto i : s) {
            root[i] = i;
            sz[i] = 1;
        }
    }
}