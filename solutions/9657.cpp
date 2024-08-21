#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

ll N, tree[4*MAXN], n;

void update(int x, ll v, int s = 0, int e = n-1, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] += v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int query(ll kth, int s = 0, int e = n-1, int idx = 1)
{
    if(s == e) return s;

    int m = (s + e) / 2;
    if(kth <= tree[2*idx]) return query(kth, s, m, 2*idx);
    else return query(kth - tree[2*idx], m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    vector<pair<int, int>> av(N);
    vector<int> vec;
    for(auto& [a, v] : av) {
        cin >> a >> v;
        vec.push_back(a);
    }

    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    n = vec.size();

    ll sum = 0;
    for(auto [a, v] : av) {
        int idx = lower_bound(vec.begin(), vec.end(), a) - vec.begin();
        update(idx, v);
        sum += v;
        int ans = query((sum+1)/2);
        cout << vec[ans] << "\n";
    }
}