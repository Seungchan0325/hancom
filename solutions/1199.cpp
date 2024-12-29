#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1505;
const int INF = 1e9;

struct SegTree {
    int n;
    vector<int> tree;

    SegTree(int n) : n(n), tree(2*n, -INF) {}

    void upd(int x, int v)
    {
        x--;
        for(tree[x+=n] = v; x > 1; x>>=1) tree[x>>1] = max(tree[x], tree[x^1]);
    }
    int qry(int l, int r)
    {
        if(r < 1) return -INF;
        if(n < l) return -INF;
        if(r < l) return -INF;
        l--, r--;
        int res = -INF;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) res = max(tree[l++], res);
            if(~r&1) res  = max(tree[r--], res);
        }
        return res;
    }
};

int N, R, C, A[MAXN][MAXN], DP[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> R >> C;
    vector<int> v;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> A[i][j];
            v.push_back(A[i][j]);
        }
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    vector<vector<pair<int, int>>> s(v.size());

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            int idx = lower_bound(v.begin(), v.end(), A[i][j]) - v.begin();
            s[idx].emplace_back(i, j);
        }
    }

    vector<SegTree> hor(N+2, SegTree(N)), ver(N+2, SegTree(N));

    int ans = 1;
    for(int k = 0; k < s.size(); k++) {
        for(auto [i, j] : s[k]) {
            DP[i][j] = 1 + max({
                hor[i+1].qry(1, j-2), hor[i+1].qry(j+2, N),
                hor[i-1].qry(1, j-2), hor[i-1].qry(j+2, N),
                ver[j+1].qry(1, i-2), ver[j+1].qry(i+2, N),
                ver[j-1].qry(1, i-2), ver[j-1].qry(i+2, N),
            });
            ans = max(ans, DP[i][j]);
        }
        DP[R][C] = 1;
        for(auto [i, j] : s[k]) {
            hor[i].upd(j, DP[i][j]);
            ver[j].upd(i, DP[i][j]);
        }
    }

    cout << ans;
}