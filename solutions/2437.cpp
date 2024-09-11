#include <bits/stdc++.h>

using namespace std;

int N, inDeg[256];
vector<int> graph[256];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;
    while(tc--) {
        for(int i = 'a'; i <= 'z'; i++) {
            inDeg[i] = 0;
            graph[i].clear();
        }

        cin >> N;
        vector<string> v(N);
        vector<char> cs;
        for(auto& i : v) {
            cin >> i;
            cs.insert(cs.end(), i.begin(), i.end());
        }

        sort(cs.begin(), cs.end());
        cs.erase(unique(cs.begin(), cs.end()), cs.end());
        bool CONTINUE = false;
        for(int i = 0; i < N; i++) {
            for(int j = i+1; j < N; j++) {
                int k = 0;
                while(k < min(v[i].size(), v[j].size()) && v[i][k] == v[j][k]) {
                    k++;
                }
                if(k >= min(v[i].size(), v[j].size())) {
                    if(v[i].size() > v[j].size()) {
                        CONTINUE = true;
                    }
                    continue;
                }

                graph[v[i][k]].push_back(v[j][k]);
                inDeg[v[j][k]]++;
            }
        }

        if(CONTINUE) {
            cout << "!\n";
            continue;
        }

        int remains = cs.size();
        bool ismulti = false;

        queue<int> q;
        string ans;
        for(int i : cs) {
            if(inDeg[i] == 0) {
                remains--;
                q.push(i);
                ans.push_back(i);
            }
        }

        while(!q.empty()) {
            int u = q.front(); q.pop();
            if(q.size()) ismulti = true;

            for(auto v : graph[u]) {
                if(--inDeg[v] == 0) {
                    remains--;
                    ans.push_back(v);
                    q.push(v);
                }
            }
        }

        bool flag = false;
        for(int i : cs) {
            if(inDeg[i]) {
                flag = true;
            }
        }

        if(flag) {
            cout << "!\n";
        } else if(ismulti) {
            cout << "?\n";
        } else {
            cout << ans << "\n";
        }
    }
}