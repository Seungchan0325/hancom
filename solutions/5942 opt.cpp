#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 5050;
const int MOD = 1e9 + 7;

int N, K, PSUM[MAXN][MAXN];

inline int add(int a, int b)
{
    int ret = a + b;
    if(ret >= MOD) ret -= MOD;
    return ret;
}

int main()
{
    cin >> N >> K;

    PSUM[1][1] = PSUM[2][2] = 1;
    for(int i = 3; i <= N; i+=2) PSUM[i][1] = PSUM[i-2][1];
    for(int i = 4; i <= N; i+=2) PSUM[i][2] = PSUM[i-2][2];

    int ans = (2*(K-2+1));
    for(int i = 3; i <= N; i++) {
        for(int j = 3; j <= min(i, K); j++) {
            int dp = add(PSUM[i-1][j-1], PSUM[i-j+1][j-1]);
            ans = add(ans, (((ll)dp*(K-j+1))<<1)%MOD);
            PSUM[i][j] = add(PSUM[i-2][j], dp);
        }
    }

    cout << ans;
}