#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200005;

int N;
vector<int> graph[MAXN];
ll A[MAXN], D[MAXN], P[MAXN], V[MAXN], ans;

void dfs(int u)
{
    D[u] = A[u];
    P[u] = -1e18;
    V[u] = -1e18;
    vector<ll> a;
    for(auto v : graph[u]) {
        dfs(v);
        if(D[v] > 0) D[u] += D[v];
        P[u] = max(P[u], P[v]);
        a.emplace_back(P[v]);
    }

    for(auto v : graph[u]) {
        if(D[v] <= 0) V[u] = max(V[u], D[u] + P[v]);
        if(D[v] >= 0) V[u] = max(V[u], D[u] - D[v] + V[v]);
    }

    P[u] = max(P[u], D[u]);

    sort(a.begin(), a.end(), greater<>());
    if(a.size() >= 2) {
        ans = max(ans, a[0] + a[1]);
    }
    ans = max(ans, V[u]);
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        ll par, a;
        cin >> a >> par;
        if(par != -1) graph[par].push_back(i);
        A[i] = a;
    }
    ans = -1e18;

    dfs(1);
    // for(int i = 1; i <= N; i++) {
    //     cout << D[i] << " " << P[i] << " " << V[i] << "\n";
    // }
    cout << ans;
}