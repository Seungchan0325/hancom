#include <bits/stdc++.h>

using namespace std;

int A[4][4];
vector<tuple<int, int, int>> ans = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void rotate_ri(int idx)
{
    int tmp = A[idx][3];
    A[idx][3] = A[idx][2];
    A[idx][2] = A[idx][1];
    A[idx][1] = A[idx][0];
    A[idx][0] = tmp;
}

void rotate_up(int idx)
{
    int tmp = A[3][idx];
    A[3][idx] = A[2][idx];
    A[2][idx] = A[1][idx];
    A[1][idx] = A[0][idx];
    A[0][idx] = tmp;
}

void my_find(vector<tuple<int, int, int>> path, int cangox, int cangoy)
{
    if(path.size() >= ans.size()) return;
    int cnt = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(A[i][j] != 4*i + j + 1) {
                cnt++;
            }
        }
    }

    escape:

    if(cnt == 0) {
        if(path.size() < ans.size()) {
            ans = path;
        }
        return;
    }
    if(cnt > 4*(7 - path.size())) return;
    if(path.size() >= 7) return;

    for(int i = 0; i < 4; i++) {
        if(cangox&(1<<i)) continue;
        rotate_ri(i);
        for(int j = 1; j <= 3; j++) {
            path.emplace_back(1, i+1, j);
            my_find(path, cangox|(1<<i), 0);
            path.pop_back();
            rotate_ri(i);
        }
    }

    for(int i = 0; i < 4; i++) {
        if(cangoy&(1<<i)) continue;
        rotate_up(i);
        for(int j = 1; j <= 3; j++) {
            path.emplace_back(2, i+1, j);
            my_find(path, 0, cangoy|(1<<i));
            path.pop_back();
            rotate_up(i);
        }
    }
}

int main()
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cin >> A[i][j];
        }
    }

    my_find({}, 0, 0);

    cout << ans.size() << "\n";
    for(auto [i, j, k] : ans) cout << i << " " << j << " " << k << " \n";
}