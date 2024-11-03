#include <bits/stdc++.h>

using namespace std;

struct Base {
    int X, Y, A, B, idx;
};

const int MAXN = 250005;
const int INF = 1e9;

int N, tree[4*MAXN], ans[MAXN];

void upd(int x, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    upd(x, v, s, m, 2*idx);
    upd(x, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int qry(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return -INF;

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return max(qry(l, r, s, m, 2*idx), qry(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<Base> bases(N);
    for(int i = 0; i < N; i++) {
        bases[i].idx = i + 1;
        cin >> bases[i].X >> bases[i].Y >> bases[i].A >> bases[i].B;
    }

    sort(bases.begin(), bases.end(), [](Base a, Base b) {
        return a.X < b.X;
    });
    for(auto& base : bases) {
        base.A = max(qry(1, base.Y) + 1, base.A);
        upd(base.Y, base.A);
    }

    for(int i = 1; i <= N; i++) upd(i, -INF);

    reverse(bases.begin(), bases.end());
    for(auto& base : bases) {
        base.B = min(-qry(base.Y, N) - 1, base.B);
        upd(base.Y, -base.B);
    }

    sort(bases.begin(), bases.end(), [](Base a, Base b) {
        return a.A < b.A;
    });

    priority_queue<pair<int, int>> pq;
    int idx = 0;
    for(int i = 1; i <= N; i++) {
        while(bases[idx].A <= i && idx < bases.size()) {
            pq.emplace(-bases[idx].B, bases[idx].idx);
            idx++;
        }
        if(pq.empty() || -pq.top().first < i) {
            cout << "NO\n";
            return 0;
        }
        auto [b, j] = pq.top(); pq.pop();
        ans[j] = i;
    }

    cout << "YES\n";
    for(int i = 1; i <= N; i++) cout << ans[i] << " ";
}