#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll N, M;

int main()
{
    cin >> N >> M;
    vector<pair<ll, ll>> cow(N);
    for(auto& [B, A] : cow) cin >> A >> B;
    
    vector<pair<ll, ll>> v(M);
    for(auto& [D, C] : v) cin >> C >> D;

    sort(v.begin(), v.end(), greater<>());
    sort(cow.begin(), cow.end(), greater<>());

    multiset<ll> s;
    ll idx = 0;
    ll ans = 0;
    for(auto [B, A] : cow) {
        while(idx < M && v[idx].first >= B) {
            s.insert(v[idx].second);
            idx++;
        }

        auto it = s.lower_bound(A);
        if(it == s.end()) {
            cout << "-1";
            return 0;
        }
        ans += *it;
        s.erase(it);
    }

    cout << ans;
}