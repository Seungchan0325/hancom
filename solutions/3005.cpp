#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 10005;

ll N, X[MAXN], Y[MAXN];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) cin >> X[i] >> Y[i];
    X[N] = X[0];
    Y[N] = Y[0];

    ll up = 0, down = 0;
    for(int i = 1; i <= N; i++) {
        up += X[i-1] * Y[i];
        down += Y[i-1] * X[i];
    }
    double area = abs(up - down);
    cout << fixed << setprecision(1) << area/2;
}