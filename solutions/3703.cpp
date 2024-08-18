#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;

int N, M, F[MAXN], S[MAXN], owner[MAXM], ans[MAXN];
int cnt;

void add(int m, int now)
{
    if(owner[m] == -1) {
        cnt++;
        owner[m] = now;
    } else {
        int idx = owner[m];
        if(idx < now) return;

        if(S[idx] == m) owner[m] = now;
        else {
            add(S[idx], idx);
            owner[m] = now;
        }
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> F[i] >> S[i];
    }

    memset(owner, -1, sizeof(owner));
    for(int i = N; i >= 1; i--) {
        add(F[i], i);
        ans[i] = cnt;
    }

    for(int i = 1; i <= N; i++) cout << ans[i] << "\n";
}