#include <bits/stdc++.h>

using namespace std;

const int MAXT = 105;

int N, M, T, K, X[MAXT], Y[MAXT];

int qry(int x, int y)
{
    int cnt = 0;
    for(int i = 0; i < T; i++) {
        int dx = x - X[i];
        int dy = y - Y[i];
        if(abs(dx) + abs(dy) <= K/2) cnt++;
    }
    return cnt;
}

bool in_range(int l, int r, int x)
{
    return l <= x && x <= r;
}

int main()
{
    cin >> N >> M >> T >> K;
    vector<int> xs, ys;
    for(int i = 0; i < T; i++) {
        int x, y;
        cin >> x >> y;
        X[i] = x;
        Y[i] = y;
        xs.push_back(x - y - 1);
        ys.push_back(x + y - 1);
        xs.push_back(x - y);
        ys.push_back(x + y);
        xs.push_back(x - y + 1);
        ys.push_back(x + y + 1);
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int mx = -1;
    int mxx = -1;
    int mxy = -1;

    for(int x = 0; x < xs.size(); x++) {
        for(int y = 0; y < ys.size(); y++) {
            if((xs[x] + ys[y]) % 2 || (ys[y] - xs[x]) % 2) continue;
            int rx = (xs[x] + ys[y]) / 2;
            int ry = (ys[y] - xs[x]) / 2;

            for(auto [ox, oy] : {make_pair(0, -K/2), make_pair(-K/2, 0), make_pair(K/2, 0), make_pair(0, K/2)}) {
                int nx = rx + ox;
                int ny = ry + oy;
                int cand = qry(nx, ny);
                if(cand > mx && in_range(0, N, nx) && in_range(0, M, ny)) {
                    mx = cand;
                    mxx = nx;
                    mxy = ny;
                }
            }
        }
    }

    for(int x = 0; x <= N; x++) {
        int cand = qry(x, 0);
        if(cand > mx) {
            mx = cand;
            mxx = x;
            mxy = 0;
        }

        cand = qry(x, M);
        if(cand > mx) {
            mx = cand;
            mxx = x;
            mxy = M;
        }
    }

    for(int y = 0; y <= N; y++) {
        int cand = qry(0, y);
        if(cand > mx) {
            mx = cand;
            mxx = y;
            mxy = 0;
        }

        cand = qry(N, y);
        if(cand > mx) {
            mx = cand;
            mxx = N;
            mxy = y;
        }
    }

    cout << mxx << " " << mxy << "\n";
    cout << mx;
}