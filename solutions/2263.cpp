#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, K, M;
    cin >> N >> K;

    vector<string> codes(N);
    vector<bool> visited(N, false);
    vector<int> par(N, -1);
    map<string, int> m;

    for(int i = 0; i < N; i++) {
        string s;
        cin >> s;
        codes[i] = s;
        m[s] = i;
    }

    queue<int> que;
    visited[0] = true;
    que.emplace(0);
    while(!que.empty()) {
        auto idx = que.front(); que.pop();
        string s = codes[idx];

        for(int i = 0; i < K; i++) {
            s[i] = '0' + '1' - s[i];
            if(m.count(s)) {
                int nxt = m[s];
                if(!visited[nxt]) {
                    visited[nxt] = true;
                    par[nxt] = idx;
                    que.emplace(nxt);
                }
            }
            s[i] = '0' + '1' - s[i];
        }
    }

    cin >> M;
    while(M--) {
        int J;
        cin >> J;
        J--;

        if(!visited[J]) {
            cout << -1 << "\n";
            continue;
        }

        vector<int> path;
        path.emplace_back(J);
        while(par[path.back()] != -1) {
            path.push_back(par[path.back()]);
        }

        for(int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] + 1 << " ";
        }
        cout << "\n";
    }
}