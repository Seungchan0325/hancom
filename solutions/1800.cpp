#include <bits/stdc++.h>

using namespace std;

const int MAXR = 20;

const int dr[] = {0, 0, -1, 1};
const int dc[] = {-1, 1, 0, 0};

int dist[MAXR][MAXR][MAXR][MAXR][MAXR][MAXR];
char board[MAXR][MAXR];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N;
    cin >> N;
    for(int n = 1; n <= N; n++) {
        int R, C;
        cin >> R >> C;
        int sr, sc;
        for(int r = 1; r <= R; r++) {
            for(int c = 1; c <= C; c++) {
                cin >> board[r][c];

                if(board[r][c] == 'O') {
                    sr = r;
                    sc = c;
                    board[r][c] = '.';
                }
            }
        }

        cout << "Case #" << n << ": ";

        memset(dist, 0x3f, sizeof(dist));
        deque<tuple<int, int, int, int, int, int, int>> q;
        q.emplace_back(sr, sc, 0, 0, 0, 0, 0);
        dist[sr][sc][0][0][0][0] = 0;
        while(!q.empty()) {
            auto [r, c, pr1, pc1, pr2, pc2, depth] = q.front(); q.pop_front();
            if(dist[r][c][pr1][pc1][pr2][pc2] > depth) continue;
            if(board[r][c] == 'X') {
                cout << depth << "\n";
                goto DONE;
            }

            vector<pair<int, int>> v;

            int npr = r;
            while(npr < R && board[npr+1][c] != '#') npr++;
            v.emplace_back(npr, c);

            npr = r;
            while(1 < npr && board[npr-1][c] != '#') npr--;
            v.emplace_back(npr, c);

            int npc = c;
            while(npc < C && board[r][npc+1] != '#') npc++;
            v.emplace_back(r, npc);

            npc = c;
            while(1 < npc && board[r][npc-1] != '#') npc--;
            v.emplace_back(r, npc);

            for(auto [npr, npc] : v) {
                if(dist[r][c][npr][npc][pr2][pc2] > depth) {
                    dist[r][c][npr][npc][pr2][pc2] = depth;
                    q.emplace_front(r, c, npr, npc, pr2, pc2, depth);
                }

                if(dist[r][c][pr1][pc1][npr][npc] > depth) {
                    dist[r][c][pr1][pc1][npr][npc] = depth;
                    q.emplace_front(r, c, pr1, pc1, npr, npc, depth);
                }
            }

            for(auto [npr1, npc1] : v) {
                for(auto [npr2, npc2] : v) {
                    if(dist[r][c][npr1][npc1][npr2][npc2] > depth) {
                        dist[r][c][npr1][npc1][npr2][npc2] = depth;
                        q.emplace_front(r, c, npr1, npc1, npr2, npc2, depth);
                    }
                }
            }

            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 1 || nr > R || nc < 1 || nc > C || board[nr][nc] == '#') continue;
                if(dist[nr][nc][pr1][pc1][pr2][pc2] > depth+1) {
                    dist[nr][nc][pr1][pc1][pr2][pc2] = depth+1;
                    q.emplace_back(nr, nc, pr1, pc1, pr2, pc2, depth + 1);
                }
            }

            if(pr1 == r && pc1 == c) {
                int nr = pr2;
                int nc = pc2;
                if(pr2 != 0 && dist[nr][nc][pr1][pc1][pr2][pc2] > depth+1) {
                    dist[nr][nc][pr1][pc1][pr2][pc2] = depth+1;
                    q.emplace_back(nr, nc, pr1, pc1, pr2, pc2, depth + 1);
                }
            }

            if(pr2 == r && pc2 == c) {
                int nr = pr1;
                int nc = pc1;
                if(pr1 != 0 && dist[nr][nc][pr1][pc1][pr2][pc2] > depth+1) {
                    dist[nr][nc][pr1][pc1][pr2][pc2] = depth+1;
                    q.emplace_back(nr, nc, pr1, pc1, pr2, pc2, depth + 1);
                }
            }
        }

        cout << "THE CAKE IS A LIE\n";
DONE: {}
    }
}