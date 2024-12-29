#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, l, u;

int main()
{
    cin >> n >> l >> u;
    vector<pair<ll, ll>> w(n);
    for(ll i = 0; i < n; i++) cin >> w[i].first, w[i].second = i;

    sort(w.begin(), w.end(), greater<>());

    ll lo = 0;
    ll hi = 0;
    ll s = 0;
    for(hi = 0; hi < n; hi++) {
        if(s >= l) break;
        s += w[hi].first;
    }
    if(s < l) {
        cout << "0";
        return 0;
    }
    if(s <= u) {
        cout << hi << "\n";
        for(ll i = 0; i < hi; i++) {
            cout << w[i].second << " ";
        }
        return 0;
    }
    while(true) {
        if(s <= u) {
            cout << hi - lo << "\n";
            for(ll i = lo; i < hi; i++) {
                cout << w[i].second << " ";
            }
            return 0;
        }
        if(hi >= n) break;
        s -= w[lo++].first;
        s += w[hi++].first;
    }
    cout << "0";
}