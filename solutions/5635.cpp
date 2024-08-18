#include <bits/stdc++.h>

using namespace std;

bool chk[1<<18];
int C, N, D[1<<18];

int main()
{
    cin >> C >> N;
    vector<int> v;
    for(int i = 0; i < N; i++) {
        int s = 0;
        for(int j = 0; j < C; j++) {
            char c;
            cin >> c;
            if(c == 'G') {
                s |= 1<<j;
            }
        }
        v.push_back(s);
    }

    queue<int> q;
    for(auto i : v) {
        int nxt = ~i & ((1<<C) - 1);
        q.emplace(nxt);
        chk[nxt] = true;
    }

    int depth = 0;
    while(!q.empty()) {
        int sz = q.size();
        while(sz--) {
            auto now = q.front(); q.pop();
            D[now] = depth;

            for(int i = 1; i < (1<<C); i<<=1) {
                int nxt = now ^ i;
                if(chk[nxt]) continue;
                chk[nxt] = true;
                q.emplace(nxt);
            }
        }
        depth++;
    }

    for(auto i : v) {
        cout << C - D[i] << "\n";
    }
}