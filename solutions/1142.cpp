#include <bits/stdc++.h>

using namespace std;

char A[20005];

int main()
{
    int N;
    cin >> N;
    vector<tuple<int, int, int, int>> v;
    vector<pair<int, int>> updates[20005];
    for(int i = 0; i < N; i++) {
        double _x, _y, _w, _h;
        cin >> _x >> _y >> _w >> _h;
        int x = _x * 10 + 1e-6;
        int y = _y * 10 + 1e-6;
        int w = _w * 10 + 1e-6;
        int h = _h * 10 + 1e-6;
        for(int i = y; i < y + h; i++) {
            updates[i].emplace_back(x, x + w);
        }
    }

    int area = 0;
    for(int i = 0; i <= 20000; i++) {
        memset(A, 0, sizeof(A));
        for(auto [s, e] : updates[i]) A[s]++, A[e]--;
        for(int j = 1; j <= 20000; j++) A[j] += A[j-1];
        for(int j = 0; j <= 20000; j++) if(A[j]) area++;
    }
    printf("%d", area/100);
    area %= 100;
    if(area) printf(".%02d", area);
}