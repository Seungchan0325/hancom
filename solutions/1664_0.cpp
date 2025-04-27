#include <bits/stdc++.h>

using namespace std;

const int mod = 42043;
const int K = 1001;

array<int, K> mul(const array<int, K>& a, const array<int, K>& b)
{
    array<int, K> c = {};
    for(int i = 0; i < K; i++) {
        for(int j = 0; j < K; j++) {
            if(i+j >= K) continue;
            c[i+j] += a[i] * b[j] % mod;
            c[i+j] %= mod;
        }
    }
    return c;
}

array<int, K> pw(const array<int, K>& poly, int n)
{
    if(n == 0) return {1};
    if(n&1) return mul(poly, pw(poly, n-1));
    array<int, K> half = pw(poly, n/2);
    return mul(half, half);
}

int main()
{
    int n, k, t;
    cin >> n >> k >> t;
    array<int, K> poly = {};
    for(int i = 1; i <= t; i++) {
        int a; cin >> a;
        poly[a]++;
    }
    poly = pw(poly, n);
    int ans = 0;
    for(int i = 0; i <= k; i++) {
        ans += poly[i];
        ans %= mod;
    }
    cout << ans;
}