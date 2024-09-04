#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

struct T {
    int mx;
    int mxi;
};

bool chk[MAXN];
int N, A[MAXN], nxt[MAXN], lst[MAXN], v[MAXN], cnt[MAXN];
T tree[4*MAXN];

T merge(T a, T b)
{
    if(a.mx < b.mx) return b;
    return a;
}

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].mxi = s;
        return;
    }

    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void update(int x, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx].mx += v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    init();

    int mx = -1, mxi = -1;
    for(int i = N; i >= 1; i--) {
        nxt[i] = lst[A[i]];
        lst[A[i]] = i;
        cnt[A[i]]++;
        update(A[i], 1);
    }

    for(int i = 1; i <= N; i++) {
        if(2*cnt[i] > N+1) {
            cout << "-1";
            return 0;
        }
    }

    priority_queue<int, vector<int>, greater<>> pq, erased;

    for(int i = 1; i <= N; i++) {
        if(!chk[A[i]]) {
            pq.emplace(i);
            v[A[i]] = i;
            chk[A[i]] = true;
        }
    }

    vector<int> ans;
    int next = 0;
    for(int i = 1; i <= N; i++) {
        while(pq.size() && erased.size() && pq.top() == erased.top()) {
            pq.pop(); erased.pop();
        }

        int remains = N - i + 1;
        if(2*tree[1].mx > remains) {
            int idx = v[tree[1].mxi];
            update(A[idx], -1);
            ans.push_back(idx);
            erased.push(idx);
            
            if(next) {
                v[A[next]] = next;
                pq.push(next);
            }

            next = nxt[idx];
        } else {
            if(pq.empty()) goto NOT_FOUND;

            int idx = pq.top(); pq.pop();
            update(A[idx], -1);
            ans.push_back(idx);

            if(next) {
                v[A[next]] = next;
                pq.push(next);
            }

            next = nxt[idx];
        }
    }

    for(auto i : ans) cout << i << " ";
    // cout << "\n";
    // for(auto i : ans) cout << A[i] << " ";

    return 0;
NOT_FOUND:
    cout << "-1";
}