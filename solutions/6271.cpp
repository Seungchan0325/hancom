#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, T[MAXN], S[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> T[i] >> S[i];
    vector<int> v(N);
    iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), [](int i, int j)
    {
        if(T[i] * S[j] != T[j] * S[i]) return T[i] *  S[j] < T[j] * S[i];
        return i < j;
    });
    for(auto i : v) cout << i << " ";
}