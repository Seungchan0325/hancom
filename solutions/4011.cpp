#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, A[MAXN], B[MAXN], RB[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) {
        cin >> B[i];
        RB[B[i]] = i;
    }

    vector<int> v;
    int lst = 0;
    for(int i = 1; i <= N; i++) {
        vector<int> a;
        for(int j = max(A[i]-4, 1); j <= min(A[i]+4, N-1); j++) {
            a.push_back(RB[j]);
        }
        sort(a.begin(), a.end(), greater<>());
        v.insert(v.end(), a.begin(), a.end());
    }

    vector<int> lis;
    for(auto i : v) {
        if(lis.empty() || lis.back() < i) {
            lis.push_back(i);
        } else {
            *lower_bound(lis.begin(), lis.end(), i) = i;
        }
    }

    cout << lis.size();
}