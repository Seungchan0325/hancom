#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<ll>;

const int MAXN = 1e6 + 5;

int N, K, cnt[MAXN], lst[MAXN];

int main()
{
    cin >> N >> K;
    vector<vector<pair<ll, int>>> v(K);
    vector<vi> r(N, vi(K));
    for(int i = 0; i < N; i++) {
        for(int k = 0; k < K; k++) {
            int ki;
            cin >> ki;
            v[k].emplace_back(ki, i);
        }
    }
    for(int i = 0; i < N; i++) {
        for(int k = 0; k < K; k++) {
            cin >> r[i][k];
        }
    }

    for(int k = 0; k < K; k++) {
        sort(v[k].begin(), v[k].end());
    }

    int ans = 0;
    vi p(K);
    for(int n = 0; n < N; n++) {
        for(int k = 0; k < K; k++) {
            while(lst[k] < N && v[k][lst[k]].first <= p[k]) {
                auto [val, idx] = v[k][lst[k]];
                if(++cnt[idx] == K) {
                    ans++;
                    for(int i = 0; i < K; i++) {
                        p[i] += r[idx][i];
                    }
                }
                lst[k]++;
            }
        }
    }

    cout << ans;
}