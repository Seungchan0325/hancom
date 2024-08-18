#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3505;

int N, ru[MAXN][MAXN], lu[MAXN][MAXN], ld[MAXN][MAXN], rd[MAXN][MAXN], rmx[MAXN];
char flower[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> flower[i][j];
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(flower[i-1][j-1] == flower[i][j]) {
                lu[i][j] = lu[i-1][j-1] + 1;
            } else {
                lu[i][j] = 1;
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = N; j >= 1; j--) {
            if(flower[i-1][j+1] == flower[i][j]) {
                ru[i][j] = ru[i-1][j+1] + 1;
            } else {
                ru[i][j] = 1;
            }
        }
    }

    for(int i = N; i >= 1; i--) {
        for(int j = 1; j <= N; j++) {
            if(flower[i+1][j-1] == flower[i][j]) {
                ld[i][j] = ld[i+1][j-1] + 1;
            } else {
                ld[i][j] = 1;
            }
        }
    }

    for(int i = N; i >= 1; i--) {
        for(int j = N; j >= 1; j--) {
            if(flower[i+1][j+1] == flower[i][j]) {
                rd[i][j] = rd[i+1][j+1] + 1;
            } else {
                rd[i][j] = 1;
            }
        }
    }

    int len = 0;

    for(int i = 1; i <= N; i++) {
        memset(rmx, 0, sizeof(rmx));
        int lst = N;
        for(int j = N; j >= 1; j--) {
            while(lst >= 1 && min(rd[i][lst], ru[i][lst]) >= j - lst + 1) {
                lst--;
            }
            rmx[j] = j - lst;
        }

        lst = 1;
        for(int j = 1; j <= N; j++) {
            while(lst <= N && min(ld[i][lst], lu[i][lst]) >= lst - j + 1) {
                lst++;
            }
            len = max(len, min(rmx[j], lst - j));
        }
    }

    int ans = 1;
    for(int i = 1; i < len; i++) {
        ans += 4 * i;
    }

    cout << ans << "\n";
}