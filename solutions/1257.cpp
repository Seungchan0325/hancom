#include <bits/stdc++.h>

using namespace std;

int N;

int main()
{
    cin >> N;
    vector<tuple<int, int, int>> v(N);
    int _idx = 0;
    for(auto& [a, b, idx] : v) cin >> a >> b, idx = _idx++;
    sort(v.begin(), v.end());

    vector<int> a;
    vector<int> pos(N);
    for(int i = 0; i < N; i++) {
        auto [_a, b, idx] = v[i];
        if(a.empty() || b > a.back()) {
            a.emplace_back(b);
            pos[i] = a.size() - 1;
        } else {
            auto it = lower_bound(a.begin(), a.end(), b);
            *it = b;
            pos[i] = it - a.begin();
        }
    }

    cout << N - a.size() << "\n";

    vector<int> lis;
    int lst = a.size() - 1;
    for(int i = N-1; i >= 0; i--) {
        if(lst == pos[i]) {
            lst--;
            lis.push_back(get<0>(v[i]));
        }
    }

    // sort(lis.begin(), lis.end());
    reverse(lis.begin(), lis.end());
    lst = 0;
    for(int i = 0; i < N; i++) {
        if(get<0>(v[i]) == lis[lst]) lst++;
        else cout << get<0>(v[i]) << "\n";
    }
}