#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3 * 1e5 + 5;

int N, H[MAXN], L[MAXN], R[MAXN];
char D[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> D[i];
    }
    for(int i = 1; i <= N; i++) {
        cin >> H[i];
    }

    vector<int> v;
    for(int i = 1; i <= N; i++) {
        if(D[i] == 'L') {
            if(v.empty() || v.back() < H[i]) {
                v.push_back(H[i]);
            } else {
                *lower_bound(v.begin(), v.end(), H[i]) = H[i];
            }
        }
        L[i] = v.size();
    }

    v.clear();
    for(int i = N; i >= 1; i--) {
        if(D[i] == 'R') {
            if(v.empty() || v.back() < H[i]) {
                v.push_back(H[i]);
            } else {
                *lower_bound(v.begin(), v.end(), H[i]) = H[i];
            }
        }
        R[i] = v.size();
    }

    int mx = 0;
    for(int i = 0; i <= N; i++) {
        mx = max(mx, L[i] + R[i+1]);
    }
    cout << N - mx;
}