#include <bits/stdc++.h>

using namespace std;

int N;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<pair<int, int>> lr(N);
    for(auto& [l, r] : lr) {
        int t;
        cin >> t >> l >> r;
        r = -r;
    }

    sort(lr.begin(), lr.end());
    lr.erase(unique(lr.begin(), lr.end()), lr.end());

    vector<int> lis;
    for(int i = 0; i < lr.size(); i++) {
        if(lis.empty() || lis.back() <= lr[i].second) {
            lis.push_back(lr[i].second);
        } else {
            *upper_bound(lis.begin(), lis.end(), lr[i].second) = lr[i].second;
        }
    }

    cout << lis.size();
}