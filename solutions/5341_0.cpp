#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;
    while(tc--) {
        ll s, e;
        cin >> s >> e;

        vector<ll> v1;
        ll now = s;
        while(now > 1) {
            v1.push_back(now);
            now = now&1 ? now+1 : now/2;
        }
        v1.push_back(now);

        vector<ll> v2;
        now = e;
        while(now > 1) {
            v2.push_back(now);
            now = now&1 ? now-1 : now/2;
        }
        v2.push_back(now);

        ll ans = 1e18;
        for(int i = 0; i < v1.size(); i++) {
            for(int j = 0; j < v2.size(); j++) {
                if(v1[i] <= v2[j]) ans = min(ans, i + j + v2[j] - v1[i]);
            }
        }

        cout << ans << "\n";
    }
}