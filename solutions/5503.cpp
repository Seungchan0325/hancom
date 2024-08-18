#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 105;
const ll INF = 1e18;

ll N, tC, tM;
vector<tuple<ll, ll, ll>> v;

ll f(int i)
{
    ll mn = tM;
    for(auto [A, B, C] : v) {
        if(C <= A*i) return INF + i;
        mn = min(mn, (C - A*i) / B);
    }
    if(mn <= 0) return INF + i;
    assert(mn > 0);
    return tC - i + tM - mn;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll tc;
    cin >> tc;
    while(tc--) {
        cin >> N >> tC >> tM;
        v.clear();
        for(ll i = 0; i < N; i++) {
            ll A, B;
            ll C;
            cin >> A >> B >> C;
            if(A*tC + B*tM > C) v.emplace_back(A, B, C);
        }

        ll lo = 1;
        ll hi = tC;
        while(lo + 2 < hi) {
            ll p = (2*lo + hi) / 3;
            ll q = (lo + 2*hi) / 3;

            if(f(p) > f(q)) lo = p;
            else hi = q;
        }

        ll ans = INF;
        for(ll i = max(lo-3000, 1LL); i <= min(hi+3000, tC); i++) {
            ans = min(f(i), ans);
        }
        cout << ans << "\n";

        // for(int i = 1; i <= tC; i++) {
        //     cout << i << ": " << f(i) << "\n";
        //     // f(i);
        //     // cout << " ";
        // }
        // cout << "\n";
    }
}