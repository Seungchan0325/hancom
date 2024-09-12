#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int N, Q, P[MAXN], root[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    root[y] = x;
}

int main()
{
    cin >> N >> Q;

    for(int i = 2; i <= N; i++) {
        cin >> P[i];
    }

    iota(root, root + N + 1, 0);

    Q += N-1;

    vector<tuple<int, int, int>> queries;

    while(Q--) {
        int x;
        cin >> x;

        if(x == 0) {
            int b;
            cin >> b;
            queries.emplace_back(x, b, 0);
        } else {
            int c, d;
            cin >> c >> d;
            queries.emplace_back(x, c, d);
        }
    }

    reverse(queries.begin(), queries.end());

    stack<int> s;

    for(auto [x, a, b] : queries) {
        if(x == 0) {
            merge(a, P[a]);
        } else {
            if(find(a) == find(b)) {
                s.push(1);
            } else {
                s.push(0);
            }
        }
    }

    while(s.size()) {
        if(s.top()) cout << "YES\n";
        else cout << "NO\n";
        s.pop();
    }
}