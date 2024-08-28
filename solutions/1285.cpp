#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

bool chk[MAXN];
int P[MAXN], nxt[MAXN], lst[MAXN];

int main()
{
    int z = 4;
    cin >> z;
    for(int tc = 0; tc < z; tc++) {
        int N, M;
        cin >> N >> M;
        for(int i = 1; i <= M; i++) cin >> P[i];

        memset(nxt, 0, sizeof(nxt));
        memset(lst, 0, sizeof(lst));
        for(int i = M; i >= 1; i--) {
            nxt[i] = lst[P[i]];
            lst[P[i]] = i;
        }
        
        memset(chk, 0, sizeof(chk));
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 1; i <= M; i++) {
            if(!P[i]) continue;
            if(!chk[P[i]]) {
                pq.push(i);
                chk[P[i]] = true;
            }
        }

        memset(chk, 0, sizeof(chk));
        vector<int> ans;
        for(int i = 1; i <= M; i++) {
            if(P[i]) {
                if(nxt[i]) {
                    pq.push(nxt[i]);
                }
                if(!chk[P[i]]) {
                    goto NO;
                }
                chk[P[i]] = false;
            } else {
                if(pq.empty()) {
                    ans.push_back(0);
                } else {
                    int idx = pq.top(); pq.pop();
                    ans.push_back(P[idx]);
                    chk[P[idx]] = true;
                }
            }
        }

        cout << "YES\n";
        for(int i : ans) cout << i << " ";
        cout << "\n";

        continue;
NO:
        cout << "NO\n";
    }
}