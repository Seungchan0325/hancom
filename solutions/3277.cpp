#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

ll f(ll x)
{
    return x*(x+1)/2;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    for(int i = 0; i < 5; i++) {
        long long N;
        cin >> N;

        ll l = (N+2)/3;
        ll r = (N+1)/2-1;
        ll ans = f(r)-f(l-1)+(r-l+1);

        if(N&1) {
            ll El = l/2;
            ll Er = (r+1)/2;
            ll Ol = (l-1)/2;
            ll Or = r/2;

            ans -= (N*(Er-El)-((2*f(Er)-Er)-(2*f(El)-El)))/2;
            ans -= (N*(Or-Ol)-((2*f(Or))-(2*f(Ol)))+Or-Ol)/2;
        } else {
            ll El = (l-1)/2;
            ll Er = r/2;
            ll Ol = l/2;
            ll Or = (r+1)/2;

            ans -= (N*(Er-El)-2*(f(Er)-f(El)))/2;
            ans -= (N*(Or-Ol)-((2*f(Or)-Or)-(2*f(Ol)-Ol))+Or-Ol)/2;
        }

        // for(ll a = l; a <= r; a++) {
        //     ans -= (N-a+1)/2;
        // }

        cout << (long long)ans << '\n';
    }
}