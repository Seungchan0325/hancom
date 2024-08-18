#include <bits/stdc++.h>

using namespace std;

int main()
{
    while(true) {
        int N, M;
        cin >> N >> M;
        if(N == 0) break;

        vector<int> graph[N];

        for(int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<bool> visited(1<<N);

        int dep = 0;
        queue<pair<int, vector<int>>> q;
        q.push({(1<<N)-1, {}});
        visited[(1<<N)-1] = true;
        while(!q.empty()) {
            int sz = q.size();
            for(int i = 0; i < sz; i++) {
                auto [state, path] = q.front(); q.pop();
                int cnt = __builtin_popcount(state);
                if(state == 0) {
                    cout << dep << ": ";
                    for(int j : path) cout << j << " ";
                    cout << "\n";
                    goto FOUND;
                }

                for(int i = 0; i < N; i++) {
                    int nxt = 0;
                    for(int j = 0; j < N; j++) {
                        for(int k : graph[j]) {
                            if(k == i) continue;
                            if(state & (1<<k)) {
                                nxt |= 1<<j;
                            }
                        }
                    }
                    // int ncnt = __builtin_popcount(nxt);

                    if(!visited[nxt]) {
                        visited[nxt] = true;
                        path.push_back(i);
                        q.emplace(nxt, path);
                        path.pop_back();
                    }
                }
            }
            dep++;
        }

        cout << "Impossible\n";
        continue;
FOUND: {}
    }
}