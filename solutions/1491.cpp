#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 105;

ll S, N, D[MAXN], T[MAXN], cache[MAXN];
vector<ll> ans;

ll dp(ll n)
{
    if(n == N+1) return 0;
    ll& ret = cache[n];
    if(ret != -1) return ret;

    ret = 1e18;
    for(ll nxt = n+1; nxt <= N+1; nxt++) {
        if(D[nxt] - D[n] > S) break;
        ret = min(ret, dp(nxt) + T[n]);
    }

    return ret;
}

void restruct(ll n)
{
    ans.push_back(n);
    if(n == N+1) return;
    for(ll nxt = n+1; nxt <= N+1; nxt++) {
        if(dp(nxt) + T[n] == dp(n)) {
            restruct(nxt);
            break;
        }
    }
}

int main()
{
    cin >> S >> N;
    for(ll i = 1; i <= N + 1; i++) {
        cin >> D[i];
    }
    for(ll i = 2; i <= N + 1; i++) D[i] += D[i-1];
    for(ll i = 1; i <= N; i++) {
        cin >> T[i];
    }

    memset(cache, -1, sizeof(cache));
    ll result = dp(0);
    cout << result << "\n";

    if(result == 0) return 0;

    restruct(0);
    cout << ans.size() - 2 << "\n";
    for(ll i = 1; i < ans.size()-1; i++) {
        cout << ans[i] << " ";
    }
}