#include <bits/stdc++.h>

using namespace std;

const int REF[6][4] = {
    {1, 4, 3, 5},
    {0, 5, 2, 4},
    {1, 5, 3, 4},
    {0, 4, 2, 5},
    {0, 1, 2, 3},
    {0, 3, 2, 1}
};

int main()
{
    string s[4];
    for(int i = 0; i < 4; i++) cin >> s[i];

    set<pair<char, array<string, 4>>> st;

    for(int top = 0; top < pow(6, 4); top++) {
        int remains = top;
        vector<int> t;
        for(int i = 0; i < 4; i++) {
            t.push_back(remains%6);
            remains /= 6;
        }
        for(int rot = 0; rot < pow(4, 4); rot++) {
            remains = rot;
            vector<int> r;
            for(int i = 0; i < 4; i++) {
                r.push_back(remains%4);
                remains /= 4;
            }

            bool flag = true;
            array<string, 4> sides;
            for(int side = 0; side < 4; side++) {
                string str;
                for(int i = 0; i < 4; i++) {
                    str += s[i][REF[t[i]][(side+r[i])%4]];
                }
                sides[side] = str;
                sort(str.begin(), str.end());
                for(int i = 1; i < 4; i++) {
                    if(str[i-1] == str[i]) {
                        flag = false;
                    }
                }
                if(!flag) break;
            }

            for(int i = 0; i < 4; i++) {
                rotate(sides.begin(), sides.begin()+1, sides.end());
                if(st.count(make_pair(s[3][t[3]], sides))) {
                    flag = false;
                    break;
                }
            }

            if(flag)
                st.insert(make_pair(s[3][t[3]], sides));
        }
    }
    cout << st.size();
}