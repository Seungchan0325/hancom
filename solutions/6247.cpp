#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;
const int LOGN = 20;

int N, K, P[MAXN], height[MAXN], leaf[MAXN];
vector<int> leaves;
vector<int> tree[MAXN];

void dfs(int u)
{
    if(tree[u].empty()) {
        height[u] = 1;
        leaf[u] = u;
        leaves.push_back(u);
        return;
    }
    for(auto v : tree[u]) {
        dfs(v);
        if(height[u] < height[v]) {
            height[u] = height[v];
            leaf[u] = leaf[v];
        }
    }
    height[u]++;
    height[leaf[u]]++;
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i < N; i++) cin >> P[i];
    for(int i = 1; i < N; i++) {
        tree[P[i]].push_back(i);
    }

    dfs(0);
    sort(leaves.begin(), leaves.end(), [](int i, int j){return height[i] > height[j];});
    int sum = 0;
    int cnt = 0;
    for(int i = 0; i < leaves.size(); i++) {
        if(sum >= N-K) break;
        sum += height[leaves[i]];
        cnt++;
    }
    cout << cnt;
}