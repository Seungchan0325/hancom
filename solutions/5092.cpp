#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using tiii = tuple<int, int, int>;

const ll MAXN = 55;
const ll MAXT = 100005;

ll N, T, DP[MAXN][MAXT], M[MAXN], P[MAXN], R[MAXN];

int main()
{
    cin >> N >> T;
    for(ll i = 1; i <= N; i++) cin >> M[i];
    for(ll i = 1; i <= N; i++) cin >> P[i];
    for(ll i = 1; i <= N; i++) cin >> R[i];

    vector<tuple<int, int, int>> v;
    for(int i = 1; i <= N; i++) {
        v.emplace_back(M[i], P[i], R[i]);
    }
    sort(v.begin(), v.end(), [](tiii x, tiii y) {
        auto [mx, px, rx] = x;
        auto [my, py, ry] = y;
        return rx * py < ry * px;
    });

    ll ans = 0;

    for(ll i = 1; i <= N; i++) {
        auto [m, p, r] = v[i-1];
        for(ll t = 0; t <= T; t++) {
            DP[i][t] = DP[i-1][t];
            if(t >= r) {
                DP[i][t] = max(DP[i][t], DP[i-1][t-r] + m - t*p);
            }
            ans = max(ans, DP[i][t]);
        }
    }

    cout << ans;
}