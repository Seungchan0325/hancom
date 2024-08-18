#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

bool A[MAXN];
int N, M, cache[MAXN][MAXN];

int dp(int i, int coupons)
{
    if(i > N) return 0;
    int& ret = cache[i][coupons];
    if(ret != -1) return ret;

    ret = 1e8;

    if(A[i]) ret = min(ret, dp(i+1, coupons));
    if(coupons >= 3) ret = min(ret, dp(i+1, coupons-3));

    ret = min(ret, dp(i+1, coupons) + 10000);
    ret = min(ret, dp(i+3, coupons+1) + 25000);
    ret = min(ret, dp(i+5, coupons+2) + 37000);

    return ret;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int a;
        cin >> a;
        A[a] = true;
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(1, 0);
    cout << result;
}