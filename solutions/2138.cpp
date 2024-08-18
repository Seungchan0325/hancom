#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int N, M, DP[MAXN][1<<4];

int main()
{
    cin >> N >> M;

    DP[1][0] = 1;
    for(int i = 1; i <= N; i++) {
        DP[i+1][0] = (DP[i+1][0] + DP[i][0]) % M;
        for(int j = 0; j < 1<<4; j++) {
            DP[i+1][~j&0b1111] = (DP[i+1][~j&0b1111] + DP[i][j]) % M;
            for(int k = 0b11; k < 1<<4; k<<=1) {
                if(((~j&k)&0b1111) == k) {
                    DP[i+1][(~j&~k)&0b1111] = (DP[i+1][(~j&~k)&0b1111] + DP[i][j]) % M;
                }
            }
        }
    }

    cout << DP[N+1][0];
}