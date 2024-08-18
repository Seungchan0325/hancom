#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2505;

int N, A[MAXN], DP[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    for(int i = 1; i <= N; i++) {
        DP[i] = DP[i-1] + 1;
        int remains = A[i];
        for(int j = i-1; j > 0; j--) {
            remains = A[j] - remains;
            if(remains < 0) break;
            if(remains == 0) DP[i] = min(DP[i], DP[j-1] + i - j);
        }
    }

    cout << DP[N];
}