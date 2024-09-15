#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

const int MAXN = 1005;
const int MAXK = 45;

int K, N, X[MAXN], Y[MAXN], R[MAXN], S[MAXN];
vector<tuple<int, int, int>> edges;
vector<pair<int, int>> graph[MAXK];

int main()
{
    cin >> K >> N;
    for(int i = 1; i <= N; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        edges.emplace_back(x-1, y, r);
        edges.emplace_back(y, x-1, -r);
    }
    for(int i = 1; i <= K; i++) {
        edges.emplace_back(i-1, i, 1);
        edges.emplace_back(i, i-1, 0);
    }

    fill(S, S + K + 1, INF);
    S[0] = 0;
    for(int i = 0; i <= N; i++) {
        for(auto [u, v, w] : edges) {
            if(S[u] >= INF) continue;
            
            if(S[u] + w < S[v]) {
                S[v] = S[u] + w;
            }
        }
    }

    bool neg_cycle = false;
    for(auto [u, v, w] : edges) {
        if(S[u] >= INF) continue;

        if(S[u] + w < S[v]) {
            neg_cycle = true;
            S[v] = S[u] + w;
        }
    }

    if(neg_cycle) {
        cout << "NONE";
        return 0;
    }

    for(int i = 1; i <= K; i++) {
        if(S[i] - S[i-1]) cout << "#";
        else cout << "-";
    }
}