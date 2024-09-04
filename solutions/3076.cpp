#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000006;

bool chk[MAXN];
int N, X[2*MAXN], Y[2*MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> X[i] >> Y[i];
        X[i+N] = X[i];
        Y[i+N] = Y[i];
    }

    int start;
    for(int i = 1; i <= N; i++) {
        if(Y[i] < 0) {
            start = i;
            break;
        }
    }

    int pv = 0;
    vector<pair<int, int>> v;
    int px = X[start];
    int py = Y[start];
    for(int i = start+1; i <= N + start; i++) {
        if(py < 0 && Y[i] > 0) { // up
            v.emplace_back(X[i], ++pv);
        } else if(py > 0 && Y[i] < 0) {// down
            v.emplace_back(X[i], pv);
        }
        px = X[i];
        py = Y[i];
    }

    sort(v.begin(), v.end());

    int cnt1 = pv;
    int cnt2 = 0;

    for(int i = 1; i < v.size(); i++) {
        if(v[i-1].second == v[i].second) cnt2++;
    }

    stack<int> s;
    for(auto [x, idx] : v) {
        if(chk[idx]) {
            while(s.top() != idx) {
                s.pop();
            }
            s.pop();
            if(s.size()) cnt1--;
        } else {
            chk[idx] = true;
            s.push(idx);
        }
    }

    cout << cnt1 << " " << cnt2;
}