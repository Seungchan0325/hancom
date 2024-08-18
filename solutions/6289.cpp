#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150005;

int N, M, tree[4*MAXN];

void update(int pos, int delta, int s = 1, int e = N, int idx = 1)
{
    if(e < pos || pos < s) return;

    if(s == e) {
        tree[idx] += delta;
        return;
    }

    int m = (s + e) / 2;
    update(pos, delta, s, m, 2*idx);
    update(pos, delta, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int v, int s = 1, int e = N, int idx = 1)
{
    if(s == e) return s;

    int m = (s + e) / 2;
    if(tree[2*idx] >= v) return query(v, s, m, 2*idx);
    else if(tree[2*idx+1] >= v) return query(v, m+1, e, 2*idx+1);
    return 0;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        update(i, a);
    }

    for(int i = 1; i <= M; i++) {
        int a;
        cin >> a;
        int idx = query(a);
        cout << idx << " ";
        update(idx, -a);
    }
}