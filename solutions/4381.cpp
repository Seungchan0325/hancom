#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

int N, M, tree[MAXN];

void update(int i, int delta)
{
    while(i <= N) {
        tree[i] += delta;
        i += i & -i;
    }
}

int query(int i)
{
    int ret = 0;
    while(i > 0) {
        ret += tree[i];
        i -= i & -i;
    }
    return ret;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        int ai;
        cin >> ai;
        update(i, ai);
    }

    while(M--) {
        int l, i, r, s, j, e;
        cin >> l >> i >> r >> s >> j >> e;
        
        int pi = query(r) - query(l-1);
        int pj = query(e) - query(s-1);
        if(pi != pj) {
            if(pi > pj) {
                swap(l, s);
                swap(i, j);
                swap(r, e);
            }

            int x = query(i) - query(i-1);
            update(i, -(x+1)/2);
            update(j, (x+1)/2);
        }
    }

    for(int i = 1; i <= N; i++) {
        cout << query(i) - query(i-1) << " ";
    }
}