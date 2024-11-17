#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll N, R, M;

int main()
{
    cin >> N >> R >> M;
    vector<ll> xs;
    for(int i = 0; i < N; i++) {
        ll x;
        cin >> x;
        xs.push_back(x);
        xs.push_back(x+M);
    }
    sort(xs.begin(), xs.end());

    ll mn = 1e18;
    ll mx = 0;
    for(int i = 0; i < xs.size(); i++) {
        mx = max(mx, xs[i] - 2*R*i - mn);
        mn = min(mn, xs[i] - 2*R*i);
    }

    cout << (mx+1)/2;
}