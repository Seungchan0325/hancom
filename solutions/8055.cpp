#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200005;
const ll MOD = 1e9 + 7;

struct T {
    ll cnt;
    ll sum;
};

T merge(T a, T b)
{
    return {a.cnt + b.cnt, (a.sum + b.sum) % MOD};
}

int N;
T tree[4*MAXN];

void update(int x, T a, int s = 0, int e = MAXN, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = merge(tree[idx], a);
        return;
    }

    int m = (s + e) / 2;
    update(x, a, s, m, 2*idx);
    update(x, a, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 0, int e = MAXN, int idx = 1)
{
    if(e < l || r < s) return {0, 0};

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    cin >> N;
    int Xi;
    cin >> Xi;
    update(Xi, {1, Xi});

    ll ans = 1;
    for(int i = 2; i <= N; i++) {
        cin >> Xi;
        T l = query(0, Xi-1);
        T r = query(Xi+1, MAXN);
        ll t = l.cnt * Xi % MOD - l.sum + r.sum - r.cnt * Xi % MOD;
        t = (t % MOD + MOD) % MOD;
        ans *= t;
        ans %= MOD;

        update(Xi, {1, Xi});
    }
    cout << ans;
}