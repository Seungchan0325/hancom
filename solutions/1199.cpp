// #pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1505;
const int INF = 1e9;

struct st {
    vector<pair<int, int>> s;

    void upd(int x, int v)
    {
        s.emplace_back(v, x);
        sort(s.begin(), s.end(), greater<>());
        if(s.size() > 4) s.pop_back();
    }
    int qry(int i, int j, int k)
    {
        for(auto [v, x] : s) {
            if(x != i && x != j && x != k) return v;
        }
        return -INF;
    }
};

int N, R, C, A[MAXN][MAXN], DP[MAXN][MAXN];
st hor[MAXN], ver[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> R >> C;
    vector<int> v;
    v.reserve(N*N);
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

    int ans = 1;
    for(int k = 0; k < s.size(); k++) {
        for(auto [i, j] : s[k]) {
            DP[i][j] = 1 + max({
                hor[i+1].qry(j-1, j, j+1),
                hor[i-1].qry(j-1, j, j+1),
                ver[j+1].qry(i-1, i, i+1),
                ver[j-1].qry(i-1, i, i+1),
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