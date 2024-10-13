#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

vector<pair<int, int>> v;
bool vst[MAXN];
int N, X[MAXN], Y[MAXN], DX[MAXN][MAXN], DY[MAXN][MAXN];

int MaxPair(int idx)
{
    if(idx == N) {
        int cnt = 0;
        for(int i = 0; i < v.size(); i++) {
            for(int j = 0; j < i; j++) {
                if(v[i] == v[j]) {
                    cnt++;
                }
            }
        }
        return cnt;
    }

    if(vst[idx]) return MaxPair(idx+1);

    int mx = 0;
    for(int i = idx+1; i <= N; i++) {
        if(vst[i]) continue;
        v.emplace_back(DX[idx][i], DY[idx][i]);
        vst[i] = true;
        mx = max(mx, MaxPair(idx+1));
        vst[i] = false;
        v.pop_back();
    }

    return mx;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> X[i] >> Y[i];

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(i == j) continue;
            int x = X[i] - X[j];
            int y = Y[i] - Y[j];
            if(x < 0) {
                x = -x;
                y = -y;
            }
            int g = gcd(x, y);
            x /= g;
            y /= g;
            if(!x || !y) x = abs(x), y = abs(y);
            DX[i][j] = x;
            DY[i][j] = y;
        }
    }

    int result = MaxPair(1);
    cout << result;
}