#include <bits/stdc++.h>

using namespace std;

const int MAXN = 15;
const int MAXC = 50;

int N, C, B[MAXN], P[MAXC], cache[1<<MAXN], cost[1<<MAXN];

int dp(int taken)
{
    if(taken == (1<<N)-1) return 0;
    int& ret = cache[taken];
    if(ret != -1) return ret;

    for(int bit = 1; bit < (1<<N); bit++) {
        if(taken&bit) continue;

        ret = max(ret, dp(taken|bit) + cost[bit]);
    }

    return ret;
}

int main()
{
    cin >> C >> N;
    for(int i = 0; i < N; i++) cin >> B[i];
    for(int i = 0; i <= C; i++) cin >> P[i];

    for(int bit = 1; bit < (1<<N); bit++) {
        int cnt = 0;
        int ccnt = 0;
        int sum = 0;
        int c = 0;
        for(int i = 0; i < N; i++) {
            if(bit&(1<<i)) {
                cnt++;
                sum += B[i];

                if(sum > C) {
                    c += P[C];
                    sum -= C;
                    ccnt++;
                }
            }
        }

        if(sum) {
            c += P[sum];
            ccnt++;
        }

        c += (cnt - ccnt) * P[0];

        cost[bit] = c;
    }

    memset(cache, -1, sizeof(cache));
    int result = dp(0);
    cout << result;
}