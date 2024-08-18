#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1000005;
const ll MOD = 1e9 + 7;

ll DP[MAXN];

ll pow(int x, int n)
{
    if(n == 0) return 1;
    if(n&1) return pow(x, n-1)*x % MOD;
    ll half = pow(x, n/2);
    return half*half % MOD;
}

int main()
{
    int N;
    cin >> N;

    if(N == 1) {
        cout << 3;
        return 0;
    }

    ll result = 3*2*(pow(2, N-1)-1) % MOD;
    result = (result + 2*2*(pow(2, N-2)-1) + 2 + 3) % MOD;

    cout << result;
}