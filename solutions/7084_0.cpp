#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 505;
const int MOD = 1e9 + 7;

int N, a[MAXN], b[MAXN], P[MAXN], Q[MAXN], DP[MAXN][MAXN], S[MAXN][MAXN][MAXN];
vector<int> v[MAXN], u[MAXN];

struct cmp {
    int* P;
    int i;
    cmp(int P[], int i) : i(i), P(P) {}
    bool operator() (int a, int b) const {
        return (P[i] - P[a]) * (i - b) < (P[i] - P[b]) * (i - a); 
    }
};

signed main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> a[i];
    for(int i = 1; i <= N; i++) cin >> b[i];
    for(int i = 1; i <= N; i++) {
        P[i] = P[i-1] + a[i];
    }
    for(int i = 1; i <= N; i++) {
        Q[i] = Q[i-1] + b[i];
    }

    for(int i = 1; i <= N; i++) {
        u[i].resize(i);
        iota(u[i].begin(), u[i].end(), 0);
        sort(u[i].begin(), u[i].end(), cmp(P, i));

        v[i].resize(i);
        iota(v[i].begin(), v[i].end(), 0);
        sort(v[i].begin(), v[i].end(), cmp(Q, i));
    }

    DP[0][0] = 1;
    for(int i = 1; i <= N; i++) {
        for(int a = 0; a < i; a++) {
            for(int b = 0; b < N; b++) {
                S[i][a][b] = (S[i][a-1][b] + DP[u[i][a]][b]) % MOD;
                if(a == 0) S[i][a][b] = DP[u[i][a]][b];
            }
        }

        for(int j = 1; j <= N; j++) {
            int l = -1;
            const auto& p = u[i];
            const auto& q = v[j];
            for(int k = 0; k < q.size(); k++) {
                while(l+1 < p.size() && (P[i]-P[p[l+1]])*(j-q[k]) <= (Q[j]-Q[q[k]])*(i-p[l+1])) {
                    l++;
                }
                DP[i][j] = (DP[i][j] + S[i][l][q[k]]) % MOD;
            }
        }
    }

    cout << DP[N][N];
}