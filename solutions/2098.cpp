#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50;

int N, K, cache[MAXN][1<<3][2];

int f(int idx, int taken, int free)
{
    if(idx == N+1) {
        return 1;
    }
    int& ret = cache[idx][taken][free];
    if(ret != -1) return ret;

    if(idx == 1) taken |= 1;
    if(idx == N) taken |= 4;
    if(idx+1 == K) taken |= 4;
    
    if(idx == K) {
        taken |= 2;
        ret = f(idx+1, taken>>1, free);
        return ret;
    }

    ret = 0;
    if(~taken&1) ret += f(idx+1, taken>>1, free);
    if(~taken&2) ret += f(idx+1, taken>>1|1, free);
    if(~taken&4) ret += f(idx+1, taken>>1|2, free);

    if(!free) {
        ret += f(idx+1, taken>>1, true);
    }

    return ret;
}

int main()
{
    cin >> N >> K;
    memset(cache, -1, sizeof(cache));
    int result = f(1, 0, false);
    cout << result;
}