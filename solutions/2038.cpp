#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int N, DP[MAXN];

signed main()
{
    cin >> N;
    vector<pair<int, int>> v(N);
    for(auto& [x, y] : v) cin >> x >> y;
    v.emplace_back(-1e9, 0);
    sort(v.begin(), v.end());

    for(int i = 1; i <= N; i++) {
        int maxh = 0;
        DP[i] = 1e9;
        for(int j = i; j > 0; j--) {
            maxh = max(maxh, abs(v[j].second));
            int cost = max(2*maxh, v[i].first - v[j].first);
            DP[i] = min(DP[i], DP[j-1] + cost);
        }
    }

    cout << DP[N];
}