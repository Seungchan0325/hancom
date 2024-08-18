#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;
    while(tc--) {
        ll s[2];
        cin >> s[0] >> s[1];

        int ans = -1;
        map<ll, pair<int, int>> chk;
        queue<pair<ll, int>> q[2];
        q[0].emplace(s[0], 0); chk[s[0]] = {1, 0};
        q[1].emplace(s[1], 0); chk[s[1]] = {2, 0};
        if(s[0] == s[1]) {
            ans = 0;
            goto FOUND;
        }

        while(true) {
            int sz = q[0].size();
            while(sz--) {
                auto [now, dep] = q[0].front(); q[0].pop();

                vector<ll> v;
                v.reserve(3);
                if((now > s[1] && (now&1) || now < s[1])) v.push_back(now+1);
                if(now < s[1]) v.push_back(2*now);
                if(now%2 == 0) v.push_back(now/2);

                for(auto nxt : v) {
                    auto [g, d] = chk[nxt];
                    if(g == 2) {
                        ans = d + dep + 1;
                        goto FOUND;
                    } else {
                        if(g == 0) {
                            chk[nxt] = {1, dep + 1};
                            q[0].emplace(nxt, dep+1);
                        }
                    }
                }
            }

            sz = q[1].size();
            while(sz--) {
                auto [now, dep] = q[1].front(); q[1].pop();

                vector<ll> v;
                v.reserve(3);
                v.push_back(now-1);
                if(now < s[0]) v.push_back(2*now);
                if(now%2 == 0) v.push_back(now/2);

                for(auto nxt : v) {
                    auto [g, d] = chk[nxt];
                    if(g == 1) {
                        ans = d + dep + 1;
                        goto FOUND;
                    } else {
                        if(g == 0) {
                            chk[nxt] = {2, dep + 1};
                            q[1].emplace(nxt, dep+1);
                        }
                    }
                }
            }
        }
FOUND:
        cout << ans << "\n";
    }
}