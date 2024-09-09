#include <bits/stdc++.h>

using namespace std;

struct T {
    int L;
    int R;
    int mx;
};

T merge(T a, T b)
{
    T ret;
    ret.L = a.L + b.L;
    ret.R = a.R + b.R;
    ret.mx = max(a.mx + b.R, a.L + b.mx);
    return ret;
}

const int MAXN = 100005;

int N, Q;
string s;
T tree[4*MAXN];

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
    cin >> s;
    N = s.size();
    
    s = ' ' + s;
    for(int i = 1; i <= N; i++) {
        update(i, {s[i] == 'L', s[i] == 'R', 1});
    }

    cin >> Q;
    while(Q--) {
        int p;
        char c;
        cin >> p >> c;
        update(p, {c == 'L', c == 'R', 1});
        cout << tree[1].mx << "\n";
    }
}