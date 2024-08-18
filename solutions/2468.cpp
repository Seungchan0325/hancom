#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

int main()
{
    ull A;
    cin >> A;

    bool upd = false;
    ull mn = A, mx = A;
    for(int i = 0; i < 60; i++) {
        if(A&(1LL<<i) && !(A&(1LL<<(i+1)))) {
            mx ^= (1LL<<i);
            mx |= (1LL<<(i+1));
            int lo = i - 1;
            for(int j = i - 1; lo >= 0; j--, lo--) {
                while(A&(1LL<<lo)) {
                    lo--;
                }

                if(lo < 0) break;

                if(lo < j) {
                    mx &= ~(1LL<<j);
                    mx |= (1LL<<lo);
                }
            }
            break;
        }
    }

    for(int i = 1; i <= 60; i++) {
        if(!(A&(1LL<<(i-1))) && A&(1LL<<i)) {
            mn ^= (1LL<<i);
            mn |= (1LL<<(i-1));
            upd = true;
            int hi = 0;
            for(int j = 0; hi < i-1; j++, hi++) {
                while(A&(1LL<<hi)) {
                    hi++;
                }

                if(hi >= i-1) break;

                if(j < hi) {
                    mn &= ~(1LL<<j);
                    mn |= (1LL<<hi);
                }
            }
            break;
        }
    }

    if(upd) cout << mn << " ";
    else cout << "0 ";

    cout << mx << " ";
}