#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int N, A[MAXN];

void range_swap(int lo, int hi)
{
    while(lo < hi) {
        swap(A[lo++], A[hi--]);
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for(int i = 1; i <= N; i++) {
        if(abs(A[i] - A[i-1]) <= 1 && abs(A[i] - A[i+1]) <= 1) continue;
        for(int j = i+1; j <= N; j++) {
            if(abs(A[j] - A[j-1]) <= 1 && abs(A[j] - A[j+1]) <= 1) continue;

            range_swap(i, j);

            int s = -1;
            int e = -1;
            for(int k = 1; k <= N; k++) {
                if(A[k] != k) {
                    if(s == -1) s = k;
                    else {
                        e = k;
                    }
                }
            }

            if(s != -1 && e != -1) {
                range_swap(s, e);

                bool flag = true;
                for(int k = 1; k <= N; k++) {
                    if(A[k] != k) {
                        flag = false;
                        break;
                    }
                }

                if(flag) {
                    cout << i << " " << j << "\n";
                    cout << s << " " << e << "\n";
                    return 0;
                }

                range_swap(s, e);
            } else if(s == -1) {
                cout << i << " " << j << "\n";
                cout << "1 1\n";
                return 0;
            }

            range_swap(i, j);
        }
    }
    cout << "1 1\n1 1\n";
}