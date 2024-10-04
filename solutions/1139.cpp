#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second

const int MAXN = 105;

bool chk[MAXN][MAXN];
int N;
double cache[MAXN][MAXN];
pair<int, int> P[MAXN];

double dist(pair<int, int> a, pair<int, int> b)
{
    int x = a.X - b.X;
    int y = a.Y - b.Y;
    return sqrt(x * x + y * y);
}

double dp(int p, int i)
{
    if(i == N) return dist(P[p], P[N]);
    double& ret = cache[p][i];
    if(chk[p][i]) return ret;
    chk[p][i] = true;

    ret = dp(p, i+1) + dist(P[i], P[i+1]);

    double dd = dist(P[p], P[i+1]);
    for(int j = i+2; j <= N; j++) {
        if(j != i+2) dd += dist(P[j-2], P[j-1]);
        ret = min(ret, dp(j-1, j) + dd + dist(P[i], P[j]));
    }

    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> P[i].first >> P[i].second;
    }
    sort(P+1, P+N+1);

    double result = dp(1, 1);
    cout << setprecision(2) << fixed << round(result*100)/100;
}