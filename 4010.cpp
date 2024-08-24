#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

int N, A[MAXN], B[MAXN], RA[MAXN], tree[4*MAXN];

void update(int x, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] += v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(r < s || e < l) return 0;

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        RA[A[i]] = i;
    }
    for(int i = 1; i <= N; i++) {
        cin >> B[i];

        int idx = RA[B[i]];
        B[i] = idx;
        A[idx] = i;
    }

    ll inv = 0;
    for(int i = 1; i <= N; i++) {
        inv += query(A[i], N);
        update(A[i], 1);
    }

    vector<int> a(A+1, A+N+1);
    auto tmp = a;
    a.insert(a.end(), tmp.begin(), tmp.end());

    ll ans = inv;
    for(int i = N; i > 1; i--) {
        inv -= N - A[i];
        inv += A[i] - 1;
        ans = min(ans, inv);
    }

    inv = 0;
    memset(tree, 0, sizeof(tree));
    for(int i = 1; i <= N; i++) {
        inv += query(B[i], N);
        update(B[i], 1);
    }

    a = vector<int>(B+1, B+N+1);
    tmp = a;
    a.insert(a.end(), tmp.begin(), tmp.end());

    for(int i = N; i > 1; i--) {
        inv -= N - B[i];
        inv += B[i] - 1;
        ans = min(ans, inv);
    }

    cout << ans;
}