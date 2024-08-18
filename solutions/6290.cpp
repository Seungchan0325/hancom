#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

ll D[30], fac[30];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    D[0] = 1;
    D[2] = 1;
    for(int i = 3; i < 30; i++) {
        D[i] = (i - 1) * (D[i-1] + D[i-2]);
    }
    
    fac[0] = 1;
    fac[1] = 1;
    for(int i = 2; i < 30; i++) {
        fac[i] = fac[i-1] * i;
    }
    int tc;
    cin >> tc;
    while(tc--) {
        long long N, M;
        cin >> N >> M;

        ll cnt = fac[N];
        for(int i = 1; i <= M; i++) {
            cnt += (i&1 ? -1 : 1) * (fac[M] / fac[i] / fac[M-i]) * fac[N-i];
        }
        cout << (long long)cnt << "\n";
    }
}