#include <bits/stdc++.h>

using namespace std;

int N, sY, eX;

struct player {
    int x, y, d;
    bool operator < (const player& other) const {
        if(y != other.y) return y < other.y;
        return x < other.x;
    }
};

int main()
{
    cin >> N >> sY >> eX;
    vector<tuple<int, int, int>> v(N);
    for(auto& [x, yl, yh] : v) cin >> x >> yl >> yh;

    sort(v.begin(), v.end());
    set<player> s;
    s.insert({0, sY, 0});
    for(auto [x, yl, yh] : v) {
        auto it = s.lower_bound({-1, yl, -1});
        int mnl = 1e9;
        int mnr = 1e9;
        vector<player> erase;
        for(; it != s.end() && it->y <= yh; it++) {
            mnl = min(mnl, x - it->x + abs(it->y - yl) + it->d);
            mnr = min(mnr, x - it->x + abs(it->y - yh) + it->d);
            erase.push_back(*it);
        }

        for(auto i : erase) s.erase(i);
        s.insert({x, yl, mnl});
        s.insert({x, yh, mnr});
    }

    int mn = 1e9;
    for(auto it = s.begin(); it != s.end(); it++) {
        mn = min(mn, eX - it->x + it->d);
    }

    cout << mn << "\n";

    vector<int> ans;
    for(auto it = s.begin(); it != s.end(); it++) {
        int cand = eX - it->x + it->d;
        if(cand == mn) {
            ans.push_back(it->y);
        }
    }
    cout << ans.size() << " ";
    for(auto y : ans) cout << y << " ";
}