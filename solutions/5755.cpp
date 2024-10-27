#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250005;

struct T {
    int e, t, idx;
};

int N, M;
T tree[4*MAXN];

T merge(T a, T b)
{
    if(a.e >= b.e) return a;
    return b;
}

void update(int x, T v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(r < l) return {-1, -1, -1};
    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    if(r <= m) return query(l, r, s, m, 2*idx);
    if(m+1 <= l) return query(l, r, m+1, e, 2*idx+1);
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    vector<tuple<int, int, int>> v(N);
    vector<int> ss;
    for(auto& [s, e, t] : v) {
        cin >> s >> e >> t;
        ss.push_back(s);
    }

    sort(ss.begin(), ss.end());

    sort(v.begin(), v.end());
    int idx = 1;
    for(auto [s, e, t] : v) {
        update(idx, {e, t, idx});
        idx++;
    }

    while(M--) {
        int a, b;
        cin >> a >> b;

        int idx = upper_bound(ss.begin(), ss.end(), a) - ss.begin();
        
        long long ans = 0;
        while(true) {
            auto t = query(1, idx);
            if(t.e == -1 || t.e <= a) break;
            if(t.e > b) ans += t.t;
            update(t.idx, {-1, -1, t.idx});
        }

        idx = upper_bound(ss.begin(), ss.end(), b) - ss.begin();
        while(true) {
            auto t = query(1, idx);
            if(t.e == -1 || t.e <= b) break;
            update(t.idx, {-1, -1, t.idx});
        }

        cout << ans << "\n";
    }
}