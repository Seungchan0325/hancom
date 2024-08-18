#include <bits/stdc++.h>

using namespace std;

const int MAXM = 105;
int sqrtN;

int par[MAXM];
bool chk[MAXM];
bool graph[MAXM][MAXM];
vector<pair<int, int>> v;

int main()
{
    int N, M, A, B;
    cin >> N >> M;
    sqrtN = sqrt(N);

    for(int i = 0; i < M; i++) {
        int start, step;
        cin >> start >> step;
        v.emplace_back(start, step);
    }

    cin >> A >> B;

    queue<pair<int, int>> q;

    for(int i = 0; i < M; i++) {
        auto [start, step] = v[i];

        if(A - start >= 0 && (A - start) % step == 0) {
            q.emplace(i, 0);
            chk[i] = true;
            par[i] = -1;
        }

        if(step < sqrtN) {
            for(int j = start; j <= sqrtN; j += step) {
                for(int k = 0; k < M; k++) {
                    auto [a, m] = v[k];
                    if(j - a >= 0 && (j - a) % m == 0) {
                        graph[i][k] = true;
                        graph[k][i] = true;
                    }
                }
            }
        } else {
            for(int j = start; j <= N; j += step) {
                for(int k = 0; k < M; k++) {
                    auto [a, m] = v[k];
                    if(j - a >= 0 && (j - a) % m == 0) {
                        graph[i][k] = true;
                        graph[k][i] = true;
                    }
                }
            }
        }
    }

    while(!q.empty()) {
        auto [now, depth] = q.front(); q.pop();
        
        auto [start, step] = v[now];

        if(B - start >= 0 && (B - start) % step == 0) {
            vector<int> path;
            int u = now;
            while(u != -1) {
                path.push_back(u);
                u = par[u];
            }

            cout << depth + 1 << "\n";
            for(int i = path.size()-1; i >= 0; i--) {
                cout << path[i] + 1 << "\n";
            }
            return 0;
        }

        for(int nxt = 0; nxt < M; nxt++) {
            if(chk[nxt] || !graph[now][nxt]) continue;
            chk[nxt] = true;
            par[nxt] = now;
            q.emplace(nxt, depth + 1);
        }
    }

    cout << "-1";
}