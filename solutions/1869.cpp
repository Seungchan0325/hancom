#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 1005;
const int MAXM = 505;
const int MAXK = 10005;

vector<char> path;
int N, M, K, DP[MAXN][MAXM];
vector<tuple<int, int, char>> edges;

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        char c; cin >> c;
        path.push_back(c);
    }
    cin >> M >> K;
    for(int i = 0; i < K; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        edges.emplace_back(u, v, c);
    }

    for(int j = 0; j <= N; j++) for(int i = 1; i <= M; i++) DP[j][i] = -INF;
    DP[0][1] = 0;

    int ans = 0;
    for(int n = 1; n <= N; n++) {
        for(auto [u, v, c] : edges) {
            DP[n][u] = max(DP[n][u], DP[n-1][v] + (path[n-1] == c ? 10 : 0));
            DP[n][v] = max(DP[n][v], DP[n-1][u] + (path[n-1] == c ? 10 : 0));
            ans = max(ans, DP[n][u]);
            ans = max(ans, DP[n][v]);
        }
    }

    cout << ans;
}