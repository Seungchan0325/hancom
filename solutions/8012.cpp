#include <bits/stdc++.h>

using namespace std;

using iiii = tuple<int, int, int, int>;

const int MAXN = 200005;

int N, ans[MAXN];

struct fenwick
{
    int N;
    int tree[2*MAXN];
    fenwick(int _n) : N(_n) {}

    void update(int i, int delta)
    {
        while(i <= N) {
            tree[i] += delta;
            i += i & -i;
        }
    }

    int query(int i)
    {
        int ret = 0;
        while(i > 0) {
            ret += tree[i];
            i -= i & -i;
        }
        return ret;
    }
};

int main()
{
    cin >> N;
    vector<int> ls, rs;
    vector<iiii> v;
    for(int i = 0; i < N; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        v.emplace_back(l, r, k, i);
        ls.push_back(l);
        rs.push_back(r);
    }

    sort(ls.begin(), ls.end());
    sort(rs.begin(), rs.end());
    ls.erase(unique(ls.begin(), ls.end()), ls.end());
    rs.erase(unique(rs.begin(), rs.end()), rs.end());

    sort(v.begin(), v.end(), [](iiii a, iiii b) {
        return get<2>(a) > get<2>(b);
    });

    auto vv = v;
    sort(vv.begin(), vv.end(), [](iiii a, iiii b) {
        return get<1>(a) - get<0>(a) > get<1>(b) - get<0>(b);
    });

    fenwick ltree(ls.size());
    fenwick rtree(rs.size());
    int lst = 0;
    for(auto [l, r, k, idx] : v) {
        while(lst < N && get<1>(vv[lst]) - get<0>(vv[lst]) >= k) {
            int lidx = lower_bound(ls.begin(), ls.end(), get<0>(vv[lst])) - ls.begin() + 1;
            int ridx = lower_bound(rs.begin(), rs.end(), get<1>(vv[lst])) - rs.begin() + 1;
            ltree.update(lidx, 1);
            rtree.update(ridx, 1);
            lst++;
        }

        int lidx = upper_bound(ls.begin(), ls.end(), r - k) - ls.begin();
        int ridx = lower_bound(rs.begin(), rs.end(), l + k) - rs.begin() + 1;
        ans[idx] = ltree.query(lidx) - rtree.query(ridx-1);
    }

    for(int i = 0; i < N; i++) cout << ans[i] - 1 << "\n";
}