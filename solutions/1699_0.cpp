#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

int N;
int locker[MAXN][MAXN];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            char c;
            cin >> c;
            if(c == 'V') locker[i][j] = 1;
        }
    }

    int ans = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int cnt = 0;
            for(int k = 0; k < N; k++) {
                cnt ^= locker[i][k];
                cnt ^= locker[k][j];
            }
            if(locker[i][j]) cnt ^= 1;
            ans += cnt;
        }
    }
    cout << ans;
}