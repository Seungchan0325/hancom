#include <bits/stdc++.h>

using namespace std;

int K, A[4], pos[4];

bool dtov(vector<pair<int, int>>& v, int& d, int& dp, vector<tuple<int, int, int>>& path)
{
    if(!d) return false;

    v[0].first+=2;
    v[2].first--;
    d--;
    path.emplace_back(dp, v[2].second, v[0].second);
    sort(v.begin(), v.end());
    return true;
}

vector<tuple<int, int, int>> solve(vector<pair<int, int>> v, int d, int dp)
{
    vector<tuple<int, int, int>> path;
    sort(v.begin(), v.end());
    if(v[0].first == 0 && v[1].first == 0) {
        if(v[2].first == 0) return {};
        if(!dtov(v, d, dp, path) || !dtov(v, d, dp, path)) return vector<tuple<int, int, int>>(100000);
    }
    if((v[0].first+v[1].first+v[2].first)%2) {
        if(!dtov(v, d, dp, path)) return vector<tuple<int, int, int>>(100000);
    }
    while(v[0].first+v[1].first < v[2].first) {
        path.emplace_back(v[2].second, v[1].second, v[0].second);
        v[2].first--;
        v[1].first--;
        v[0].first+=2;
        sort(v.begin(), v.end());
    }
    while(v[0].first || v[1].first || v[2].first) {
        path.emplace_back(v[2].second, v[1].second, dp);
        v[2].first--;
        v[1].first--;
        sort(v.begin(), v.end());
    }
    return path;
}

void print()
{
    cout << A[0] << " " << A[1] << " " << A[2] << " " << A[3] << "\n";
}

int main()
{
    cin >> K;
    for(int i = 0; i < 4; i++) cin >> A[i];

    vector<tuple<int, int, int>> ans(100000);
    for(int i = 0; i < 4; i++) {
        vector<pair<int, int>> v;
        for(int j = 0; j < 4; j++) {
            if(i == j) continue;
            v.emplace_back(A[j], j);
        }
        auto cand = solve(v, A[i], i);
        if(cand.size() < ans.size()) ans = cand;
    }
    print();
    for(auto [src1, src2, dst] : ans) {
        A[src1]--;
        A[src2]--;
        A[dst]+=2;
        print();
    }
}