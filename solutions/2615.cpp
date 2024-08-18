#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 500005;

int N, a[MAXN], tree[4*MAXN];

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

int query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    vector<pair<int, int>> v(N+1);
    v[0] = {-1, -1};
    for(int i = 1; i <= N; i++) {
        v[i].second = i;
        cin >> v[i].first;
    }
    sort(v.begin(), v.end());
    for(int i = 1; i <= N; i++) {
        int id;
        cin >> id;
        auto it = lower_bound(v.begin(), v.end(), make_pair(id, 0));
        a[i] = it->second;
    }

    ll cnt = 0;
    for(int i = 1; i <= N; i++) {
        cnt += query(a[i], N);
        update(a[i], 1);
    }
    cout << cnt;
}