#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 100005;
const long long MOD = 1e9;

long long N, M, root[MAXN], sz[MAXN], chk[MAXN];
long long s;

long long find(long long x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

bool merge(long long x, long long y)
{
    x = find(x);
    y = find(y);
    if(y == x) return false;
    root[y] = x;
    s -= sz[x] * (sz[x]-1)/2;
    s -= sz[y] * (sz[y]-1)/2;
    sz[x] += sz[y];
    s += sz[x] * (sz[x]-1)/2;
    return true;
}

signed main()
{
    cin >> N >> M;
    vector<tuple<long long, long long, long long>> edges(M);
    for(auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
    }

    sort(edges.begin(), edges.end(), [](tuple<long long, long long, long long> a, tuple<long long, long long, long long> b) {
        return get<2>(a) > get<2>(b);
    });

    long long ans = 0;

    iota(root, root + N + 1, 0);
    fill(sz, sz + N + 1, 1);
    for(auto [u, v, w] : edges) {
        // if(find(u) != find(v)) {
        //     long long a = s - sz[find(u)];
        //     ans += (long long)w * ((long long)a * (a-1)) / 2;
        //     ans += (long long)w * ((long long)(sz[find(u)] * (sz[find(v)])));
        //     ans += (long long)w * ((long long)(sz[find(u)] * (sz[find(u)]-1)))/2;
        //     ans += (long long)w * ((long long)(sz[find(v)] * (sz[find(v)]-1)))/2;
        //     merge(u, v);
        //     sz[find(u)] += sz[find(v)];
        //     ans %= MOD;
        // } else {
        //     ans += (long long)w * ((long long)s * (s-1)) / 2;
        //     ans %= MOD;
        // }

        merge(u, v);
        ans += (long long)w * s;
        ans %= MOD;
    }

    cout << ans;
}