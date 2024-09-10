#include <bits/stdc++.h>

using namespace std;

struct T {
    int s[2];
};

const int MAXN = 100005;

int N, M, lazy[4*MAXN];
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    ret.s[0] = a.s[0] + b.s[0];
    ret.s[1] = a.s[1] + b.s[1];
    return ret;
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        if(lazy[idx]&1)
            swap(tree[idx].s[0], tree[idx].s[1]);

        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }

        lazy[idx] = 0;
    }
}

void build(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].s[0] = 1;
        return;
    }
    int m = (s + e) / 2;
    build(s, m, 2*idx);
    build(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void update(int l, int r, int d, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return;

    if(l <= s && e <= r) {
        lazy[idx] += d;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, d, s, m, 2*idx);
    update(l, r, d, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    if(r <= m) return query(l, r, s, m, 2*idx);
    else if(l > m) return query(l, r, m+1, e, 2*idx+1);

    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    cin >> N >> M;

    build();

    while(M--) {
        int Q, S, E;
        cin >> Q >> S >> E;

        if(Q == 0) {
            update(S, E, 1);
        } else {
            cout << query(S, E).s[1] << "\n";
        }
    }
}