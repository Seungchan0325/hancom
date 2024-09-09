#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Chalkboard {
    int n, x, ymn, ymx;
};

int P, N, tree[8*MAXN], lazy[8*MAXN];
Chalkboard chalkboard[MAXN];

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int d, int s = 0, int e = 2*N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        lazy[idx] += d;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, d, s, m, 2*idx);
    update(l, r, d, m+1, e, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 0, int e = 2*N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return MAXN;

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    cin >> P;
    cin >> N;
    vector<int> ys;
    for(int i = 0; i < N; i++) {
        cin >> chalkboard[i].n >> chalkboard[i].x >> chalkboard[i].ymn >> chalkboard[i].ymx;
        ys.push_back(chalkboard[i].ymn);
        ys.push_back(chalkboard[i].ymx);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(chalkboard, chalkboard + N, [](Chalkboard a, Chalkboard b){
        return a.x < b.x;
    });

    vector<int> ans;

    for(int i = 0; i < N; i++) {
        int l = upper_bound(ys.begin(), ys.end(), chalkboard[i].ymn) - ys.begin();
        int r = lower_bound(ys.begin(), ys.end(), chalkboard[i].ymx) - ys.begin();

        // cout << l << " " << r << '\n';

        // for(int i = 0; i < ys.size(); i++) {
        //     cout << query(i, i) << " ";
        // }
        // cout << "\n";

        int mn = query(l, r);
        if(mn >= P) ans.push_back(chalkboard[i].n);
        update(l, r, 1);
    }

    sort(ans.begin(), ans.end());

    if(ans.size()) for(auto i : ans) cout << i << " ";
    else cout << "0";
}