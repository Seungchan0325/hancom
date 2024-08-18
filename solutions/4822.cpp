#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 2005;

ll N, DP[MAXN][MAXN];

int main()
{
    cin >> N;

    vector<pair<ll, ll>> v, vv(1);
    for(ll i = 0; i < N; i++) {
        ll A, B;
        cin >> A >> B;
        if(B < 0) vv.emplace_back(A, B);
        else v.emplace_back(A, B);
    }

    sort(v.begin(), v.end(), [](pair<ll, ll> a, pair<ll, ll> b){
        if(a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    });

    vector<ll> benefit;
    ll cnt = 1;
    ll sum = 0;
    for(ll i = 0; i < v.size(); i++) {
        cnt--;
        cnt += v[i].first;
        sum += v[i].second;

        if(cnt <= 0) {
            benefit.push_back(sum);
            cnt = 1;
            sum = 0;
        }
    }
    if(sum > 0) benefit.push_back(sum);

    memset(DP, 0x80, sizeof(DP));
    DP[0][1] = 0;
    for(ll i = 1; i < vv.size(); i++) {
        auto [A, B] = vv[i];
        for(ll p = N; p >= 0; p--) {
            DP[i][p] = DP[i-1][p];
            if(p-A+1 >= 0) DP[i][p] = max(DP[i][p], DP[i-1][p-A+1] + B);
        }
    }

    ll mx = 0;
    for(ll i = 0; i < benefit.size(); i++) {
        if(i > 0) benefit[i] += benefit[i-1];
        for(ll j = i+1; j <= N; j++) {
            mx = max(mx, benefit[i] + DP[vv.size()-1][j]);
        }
    }

    cout << mx;
}