#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, M, inDeg[MAXN];
vector<int> graph[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int n;
        cin >> n;
        int prv;
        cin >> prv;
        for(int j = 2; j <= n; j++) {
            int a;
            cin >> a;
            graph[prv].push_back(a);
            inDeg[a]++;
            prv = a;
        }
    }

    int remains = N;;

    vector<int> ans;
    queue<int> q;
    for(int i = 1; i <= N; i++) {
        if(inDeg[i] == 0) {
            remains--;
            ans.push_back(i);
            q.push(i);
        }
    }
    
    while(!q.empty()) {
        auto u = q.front(); q.pop();
        for(auto v : graph[u]) {
            if(--inDeg[v] == 0) {
                remains--;
                ans.push_back(v);
                q.push(v);
            }
        }
    }

    if(remains) {
        cout << "0";
    } else {
        for(auto i : ans) cout << i << "\n";
    }
}