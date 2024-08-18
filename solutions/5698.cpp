#include <bits/stdc++.h>

using namespace std;

int fibo[50], ans[50];

int main()
{
    int N;
    cin >> N;

    fibo[0] = 1;
    fibo[1] = 1;
    for(int i = 2; i < 50; i++) fibo[i] = fibo[i-1] + fibo[i-2];

    while(N > 0) {
        int lo = 0;
        int hi = 45;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(fibo[mid] <= N) lo = mid;
            else hi = mid;
        }
        N -= fibo[lo];
        ans[lo-1] = 1;
    }

    bool flag = false;
    for(int i = 49; i >= 0; i--) {
        if(ans[i]) flag = true;

        if(flag) cout << ans[i];
    }
}