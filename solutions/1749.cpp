#include <bits/stdc++.h>

using namespace std;

const int MAXK = 505;

int b[3];
int cache[MAXK][MAXK];

bool dp(int k1, int k2)
{
    if(k1 < b[0] && k2 < b[0]) return false;
    int& ret = cache[k1][k2];
    if(ret != -1) return ret;

    ret = false;
    for(int i = 0; i < 3; i++) {
        if(k1 >= b[i]) ret |= !dp(k1 - b[i], k2);
        if(k2 >= b[i]) ret |= !dp(k1, k2 - b[i]);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> b[0] >> b[1] >> b[2];
    sort(b, b+3);
    memset(cache, -1, sizeof(cache));
    for(int i = 0; i < 5; i++) {
        int k1, k2;
        cin >> k1 >> k2;
        if(dp(k1, k2)) cout << "A\n";
        else cout << "B\n";
    }
}