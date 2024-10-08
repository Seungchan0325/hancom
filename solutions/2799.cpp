#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1000005;

ll N, A[MAXN], S[MAXN], DP1[MAXN], DP2[MAXN];

struct Line {
    ll a, b;
    double x;
    ll get(ll x)
    {
        return a * x + b;
    }
};

double cross(Line a, Line b)
{
    return (double)(a.b - b.b) / (b.a - a.a);
}

void dp(ll A[], ll DP[])
{
    S[0] = 0;
    for(ll i = 1; i <= N; i++) {
        S[i] = S[i-1] + A[i];
    }

    int lst = 0;
    vector<Line> v;
    for(int i = 1; i <= N; i++) {
        if(A[i]) {
            Line newline;
            newline.a = -S[i-1];
            newline.b = DP[i-1];
            while(v.size() > 2 && v.back().x >= cross(v.back(), newline)) v.pop_back();
            if(v.size()) newline.x = cross(v.back(), newline);
            else newline.x = -1e18;
            v.push_back(newline);

            int lo = 0;
            int hi = v.size();
            while(lo+1 < hi) {
                int mid = (lo + hi) / 2;
                if(v[mid].x < i) lo = mid;
                else hi = mid;
            }
            DP[i] = v[lo].get(i) + S[i] * i + i;
        } else {
            DP[i] = DP[i-1];
        }
    }
}

int main()
{
    cin >> N;
    for(ll i = 1; i <= N; i++) {
        cin >> A[i];
    }

    dp(A, DP1);
    reverse(A+1, A+N+1);
    dp(A, DP2);

    ll ans = 1e18;
    for(int i = 0; i <= N; i++) {
        ans = min(ans, DP1[i] + DP2[N-i]);
    }
    cout << ans;
}