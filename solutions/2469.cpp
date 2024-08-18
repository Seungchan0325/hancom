#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, tree[4*MAXN], H[MAXN], C[MAXN], ans[MAXN];

void update(int pos, int delta, int s = 1, int e = N, int idx = 1)
{
    if(e < pos || pos < s) return;

    if(s == e) {
        tree[idx] += delta;
        return;
    }

    int m = (s + e) / 2;
    update(pos, delta, s, m, 2*idx);
    update(pos, delta, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int query(int k, int s = 1, int e = N, int idx = 1)
{
    if(s == e) return s;

    int m = (s + e) / 2;
    if(tree[2*idx] <= k) {
        return query(k-tree[2*idx], m+1, e, 2*idx+1);
    } else {
        return query(k, s, m, 2*idx);
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> H[i];
    for(int i = 1; i <= N; i++) cin >> C[i];
    sort(&H[1], &H[N+1]);
    for(int i = 1; i <= N; i++) update(i, 1);

    for(int i = N; i >= 1; i--) {
        int idx = query(C[i]);
        update(idx, -1);
        ans[i] = H[idx];
    }

    for(int i = 1; i <= N; i++) cout << ans[i] << "\n";
}