#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1000005;

ll N, tree[MAXN], A[MAXN], S[MAXN], P;

void update(ll x, ll v)
{
    while(x <= N+1) {
        tree[x] += v;
        x += x&-x;
    }
}

ll query(ll x)
{
    ll ret = 0;
    while(x > 0) {
        ret += tree[x];
        x -= x&-x;
    }
    return ret;
}

int main()
{
    cin >> N;
    for(ll i = 1; i <= N; i++) {
        cin >> A[i];
        S[i] = S[i-1] + A[i];
    }
    cin >> P;

    vector<ll> v;
    for(ll i = 0; i <= N; i++) {
        v.emplace_back(S[i]-P*i);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    ll ans = 0;
    ll val = 0;
    ll idx = lower_bound(v.begin(), v.end(), val) - v.begin() + 1;
    update(idx, 1);
    for(ll i = 1; i <= N; i++) {
        val = S[i] - P*i;
        idx = lower_bound(v.begin(), v.end(), val) - v.begin() + 1;
        ans += query(idx);
        update(idx, 1);
    }
    cout << ans;
}