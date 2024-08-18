#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int N, K, ans;
vector<int> graph[MAXN];

int dfs(int u, int p)
{
    vector<int> arr;
    for(auto v : graph[u]) {
        if(v == p) continue;
        arr.push_back(dfs(v, u) + 1);
    }
    sort(arr.begin(), arr.end(), greater<>());
    bool gas = false;
    if(arr.size()) {
        if(arr[0] >= K) gas = true;
    }

    if(arr.size() >= 2) {
        if(arr[0] + arr[1] >= K) gas = true;
    }

    ans += gas;

    if(gas) return -1;
    return arr.size() ? arr[0] : 0;
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, -1);

    cout << ans;
}