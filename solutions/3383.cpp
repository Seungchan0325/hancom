#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

bool ans[MAXN], vst[MAXN], leaf[MAXN];
int N, M, in[MAXN];
vector<int> g[MAXN];
vector<int> b[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        in[u]++;
        in[v]++;
    }
    for(int i = 1; i <= M; i++) {
        int A, B;
        cin >> A >> B;
        b[A].push_back(B);
        in[B]++;
    }

    int n = 0;

    queue<int> q, q1;
    for(int i = 1; i <= N; i++) {
        if(in[i] <= 1) {
            q.push(i);
            vst[i] = true;
        }
    }

    int root = -1;

    while(!q.empty()) {
        int now = q.front(); q.pop();
        n++;
        if(n == N) {
            root = now;
        }
        for(auto nxt : b[now]) {
            in[nxt]--;
            if(in[nxt] <= 1 && !vst[nxt]) {
                vst[nxt] = true;
                q.push(nxt);
            }
        }
        for(auto nxt : g[now]) {
            in[nxt]--;
            if(in[nxt] <= 1 && !vst[nxt]) {
                vst[nxt] = true;
                q.push(nxt);
            }
        }
    }

    if(n < N) {
        for(int i = 1; i <= N; i++) cout << "0\n";
        return 0;
    }
    
    assert(root != -1);
    assert(q.empty());

    memset(vst, 0, sizeof(vst));
    q.push(root);
    vst[root] = true;

    while(!q.empty()) {
        int now = q.front(); q.pop();
        ans[now] = true;
        for(auto nxt : g[now]) {
            if(b[nxt].empty() && !vst[nxt]) {
                vst[nxt] = true;
                q.push(nxt);
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        cout << ans[i] << "\n";
    }
}