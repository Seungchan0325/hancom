#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 300005;

ll N, M, A[MAXN], B[MAXN];

bool check(__int128_t top)
{
    __int128_t cnt = 0;
    for(int i = 1; i <= N; i++) {
        __int128_t lesson = (top - 1) / A[i] + 1;
        lesson = min(lesson, (__int128_t)M);
        __int128_t self = (top - A[i] * lesson + B[i] - 1) / B[i];
        self = max((__int128_t)0, self);
        cnt += lesson + self;
    }
    return cnt <= (__int128_t)N*M;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) cin >> B[i];

    for(int i = 1; i <= N; i++) {
        A[i] = max(A[i], B[i]);
    }

    __int128_t lo = 0;
    __int128_t hi = 1e19;
    while(lo + 1 < hi) {
        __int128_t mid = (lo + hi)/2;
        if(check(mid)) lo = mid;
        else hi = mid;
    }
    cout << (ll)lo;
}