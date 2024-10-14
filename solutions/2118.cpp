#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;

int N, P[MAXN], L[MAXN], R[MAXN], A[MAXN];

int main()
{
    cin >> N;
    vector<tuple<int, int, int>> v(N);
    int i = 1;
    for(auto& [k, a, idx] : v) {
        cin >> k >> a;
        idx = i++;
    }

    sort(v.begin(), v.end());

    stack<pair<int, int>> s;
    for(auto [k, a, idx] : v) {
        int t = 0;
        while(s.size() && s.top().first > a) {
            t = s.top().second;
            s.pop();
        }
        if(s.size()) {
            R[s.top().second] = idx;
            P[idx] = s.top().second;
        }
        P[t] = idx;
        L[idx] = t;
        s.emplace(a, idx);
    }

    cout << "YES\n";
    for(int i = 1; i <= N; i++) {
        cout << P[i] << " " << L[i] << " " << R[i] << "\n";
    }
}