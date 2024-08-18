#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
const int INF = 987654321;

bool chk[MAXN*MAXN];
int N, M, K, cnt;
char jail[MAXN][MAXN];
vector<int> graph[MAXN*MAXN];

void bfs(int u)
{
    queue<int> q;
    q.push(u);
    chk[u] = true;
    cnt++;

    while(!q.empty()) {
        int now = q.front(); q.pop();
        for(auto v : graph[now]) {
            if(chk[v]) continue;
            chk[v] = true;
            cnt++;
            q.push(v);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> jail[i][j];
        }
    }

    for(int i = 1; i <= N; i++) {
        int lst = -INF;
        for(int j = 1; j <= M; j++) {
            if(j - lst <= K) {
                graph[i*M+j].push_back(i*M+lst);
            }
            if(jail[i][j] == 'R') lst = j;
        }

        lst = INF;
        for(int j = M; j >= 1; j--) {
            if(lst - j <= K) {
                graph[i*M+j].push_back(i*M+lst);
            }
            if(jail[i][j] == 'L') lst = j;
        }
    }

    for(int j = 1; j <= M; j++) {
        int lst = -INF;
        for(int i = 1; i <= N; i++) {
            if(i - lst <= K) {
                graph[i*M+j].push_back(lst*M+j);
            }
            if(jail[i][j] == 'D') lst = i;
        }

        lst = INF;
        for(int i = N; i >= 1; i--) {
            if(lst - i <= K) {
                graph[i*M+j].push_back(lst*M+j);
            }
            if(jail[i][j] == 'U') lst = i;
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            bool can_go = false;
            if(jail[i][j] == 'U' && i <= K) can_go = true;
            else if(jail[i][j] == 'D' && N+1-i <= K) can_go = true;
            else if(jail[i][j] == 'L' && j <= K) can_go = true;
            else if(jail[i][j] == 'R' && M+1-j <= K) can_go = true;

            if(can_go) {
                int u = i*M+j;
                if(!chk[u]) bfs(u);
            }
        }
    }
    cout << cnt;
}