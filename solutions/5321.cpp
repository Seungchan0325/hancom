#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int T, B, N, P[MAXN], L[MAXN], R[MAXN], DP[MAXN][3], ans[MAXN];
vector<int> graph[MAXN];

void dfs(int u)
{
    int mxL = -1;
    int mnR = 2e9;
    for(auto v : graph[u]) {
        dfs(v);
        mxL = max(DP[v][1], mxL);
        mnR = min(DP[v][2], mnR);
        DP[u][0] = max(DP[u][0], DP[v][0]);
    }
    if(mnR < mxL) {
        int m = (mnR + mxL) / 2;
        if(L[u] <= m && m <= R[u]) DP[u][0] = max(DP[u][0], mxL - m);
        else if(((mnR+mxL)&1) && L[u] <= m+1 && m+1 <= R[u]) DP[u][0] = max(DP[u][0], mxL - (m+1));
        else DP[u][0] = max(DP[u][0], max(L[u] - mnR, mxL - R[u]));
    }

    if(L[u] > mnR) {
        DP[u][0] = max(DP[u][0], L[u] - mnR);
    }
    if(mxL > R[u]) {
        DP[u][0] = max(DP[u][0], mxL - R[u]);
    }
    DP[u][1] = max(L[u], mxL);
    DP[u][2] = min(R[u], mnR);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T >> B;
    while(T--) {
        cin >> N;
        for(int i = 2; i <= N; i++) {
            cin >> P[i];
            graph[P[i]].push_back(i);
        }
        for(int i = 1; i <= N; i++) cin >> L[i] >> R[i];

        dfs(1);

        cout << DP[1][0] << "\n";

        if(B) {
            int mxL = DP[1][1];
            int mnR = DP[1][2];
            int m = (mxL + mnR) / 2;
            for(int i = 1; i <= N; i++) {
                if(L[i] <= m && m <= R[i]) cout << m << " ";
                else if(((mxL+mnR)&1) && L[i] <= m+1 && m+1 <= R[i]) cout << m+1 << " ";
                else if(abs(m-L[i]) <= abs(m-R[i])) cout << L[i] << " ";
                else cout << R[i] << " ";
            }
            cout << "\n";
        }

        for(int i = 1; i <= N; i++) graph[i].clear();
        memset(DP, 0, sizeof(DP));
    }
}