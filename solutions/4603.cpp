#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    long long N, K, Q;
    cin >> N >> K >> Q;
    long long s = 0;
    bool flag = false;
    for(long long i = 1; i <= N; i++) {
        for(long long j = 1; j <= K; j++) {
            long long a; cin >> a;
            if(i != a) {
                if(i == 1) flag = true;
                
                if(i < a) s += a - i;
                else s += N - i + a;
            }
        }
    }

    long long ans = (s + N - 1) / N;
    if(!flag) ans++;
    cout << (ans <= Q);
}
