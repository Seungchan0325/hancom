#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
const int MOD = 1e9 + 7;

int N, DP[MAXN][MAXN];
string s1, s2;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while(t--) {
        cin >> N;
        cin >> s1;
        cin >> s2;

        if(int pos = s1.rfind('0'); pos != string::npos) s1 = s1.substr(pos);
        s1.erase(remove(s1.begin(), s1.end(), '1'), s1.end());

        if(int pos = s2.rfind('0'); pos != string::npos) s2 = s2.substr(pos);
        s2.erase(remove(s2.begin(), s2.end(), '1'), s2.end());

        s1 = ' ' + s1;
        s2 = ' ' + s2;

        memset(DP, 0, sizeof(DP));
        DP[0][0] = 1;
        for(int i = 1; i <= N; i++) DP[0][i] = DP[i][0] = 1;
        for(int i = 1; i < s1.size(); i++) {
            for(int j = 1; j < s2.size(); j++) {
                DP[i][j] = (DP[i-1][j] + DP[i][j-1]) % MOD;
                if(isdigit(s1[i]) == isdigit(s2[j])) {
                    DP[i][j] -= DP[i-1][j-1];
                    DP[i][j] = (DP[i][j] + MOD) % MOD;
                }
            }
        }

        cout << DP[s1.size()-1][s2.size()-1] << "\n";
    }
}