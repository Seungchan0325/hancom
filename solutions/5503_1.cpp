#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

using ll = long long;

const ll INF = 1e18;

vector<tuple<ll, ll, ll>> v1, v2;
ll N, tc, tm;

ll g(vector<tuple<ll, ll, ll>>& v, ll sum, ll mx)
{
    ll mn = mx;
    for(auto [a, b, c] : v) {
        ll lo = 1;
        ll hi = min(sum, mx+1);
        while(lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if(a * mid + b * (sum - mid) <= c) lo = mid;
            else hi = mid;
        }
        if(a * lo + b * (sum - lo) > c) return -1;
        mn = min(lo, mn);
    }
    return mn;
}

bool f(ll sum)
{
    ll t1 = g(v1, sum, tc);
    ll t2 = g(v2, sum, tm);
    if(t1 < 0 || t2 < 0 || t1 > tc || t2 > tm) return false;
    t2 = sum - t2;
    if(t2 > tc) return false;
    return t2 <= t1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll T;
    cin >> T;
    while(T--) {
        cin >> N >> tc >> tm;
        v1.clear(); v2.clear();
        for(ll i = 0; i < N; i++) {
            ll a, b, c;
            cin >> a >> b >> c;
            if(a > b) v1.emplace_back(a, b, c);
            else v2.emplace_back(b, a, c);
        }

        ll lo = 2;
        ll hi = tc + tm + 1;
        while(lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if(f(mid)) lo = mid;
            else hi = mid;
        }

        cout << tc + tm - lo << "\n";
    }
}