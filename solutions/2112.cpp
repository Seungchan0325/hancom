#include <bits/stdc++.h>

using namespace std;

const int MAXN = 35;

int N, DP[MAXN][1<<3];

int main()
{
    cin >> N;

    DP[1][0] = 1;
    for(int i = 1; i <= N; i++) {
        // 000
        DP[i+1][0b001] += DP[i][0b000];
        DP[i+1][0b100] += DP[i][0b000];
        DP[i+1][0b111] += DP[i][0b000];
        // 001
        DP[i+1][0b000] += DP[i][0b001];
        DP[i+1][0b110] += DP[i][0b001];
        // 010
        DP[i+1][0b101] += DP[i][0b010];
        // 011
        DP[i+1][0b100] += DP[i][0b011];
        // 100
        DP[i+1][0b000] += DP[i][0b100];
        DP[i+1][0b011] += DP[i][0b100];
        // 101
        DP[i+1][0b010] += DP[i][0b101];
        // 110
        DP[i+1][0b001] += DP[i][0b110];
        // 111
        DP[i+1][0b000] += DP[i][0b111];
    }

    cout << DP[N][0b111] + DP[N][0b100] + DP[N][0b001];
}