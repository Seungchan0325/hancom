#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct T {
    int lv, llen;
    int rv, rlen;
    int mx;
    int sz;
};

bool value[MAXN];
int N, Q;
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;

    ret.lv = a.lv;
    ret.llen = a.llen;

    ret.rv = b.rv;
    ret.rlen = b.rlen;

    ret.mx = max(a.mx, b.mx);
    ret.sz = a.sz + b.sz;

    if(a.rv != b.lv) {
        ret.mx = max(a.rlen + b.llen, ret.mx);
        if(a.sz == a.llen) {
            ret.llen += b.llen;
            ret.mx = max(ret.llen, ret.mx);
        }
        if(b.sz == b.rlen) {
            ret.rlen += a.rlen;
            ret.mx = max(ret.rlen, ret.mx);
        }
    }

    return ret;
}

void update(int x, T v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        T v;
        v.lv = v.rv = 0;
        v.llen = v.rlen = 1;
        v.mx = 1;
        v.sz = 1;
        update(i, v);
    }

    while(Q--) {
        int idx;
        cin >> idx;
        
        value[idx] ^= 1;

        T v;
        v.lv = v.rv = value[idx];
        v.llen = v.rlen = 1;
        v.mx = 1;
        v.sz = 1;

        update(idx, v);

        cout << tree[1].mx << "\n";
    }
}