#include <bits/stdc++.h>

using namespace std;

int A[10][10], a[10], b[10], h[10], v[10];

int main()
{
    int bias;
    cin >> bias;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cin >> A[i][j];
            A[i][j] -= bias;
        }
    }

    for(int hi = 0; hi < pow(3, 8); hi++) {
        for(int vj = 0; vj < pow(3, 7); vj++) {
            int n = hi;
            int s = 0;
            for(int i = 0; i < 8; i++) {
                a[i] = n%3 - 1;
                s += a[i];
                n /= 3;
            }
            for(int i = 0; i < 8; i++) {
                h[i] = A[0][i] - s + a[i];
            }

            n = vj;
            b[0] = a[0];
            s = b[0];
            for(int i = 1; i < 8; i++) {
                b[i] = n%3 - 1;
                s += b[i];
                n /= 3;
            }
            for(int i = 0; i < 8; i++) {
                v[i] = A[i][0] - s + b[i];
            }

            bool flag = true;
            for(int i = 1; i < 8; i++) {
                for(int j = 1; j < 8; j++) {
                    int t = h[j] + v[i] - A[i][j];
                    if(abs(t) >= 2) {
                        flag = false;
                        break;
                    }
                    a[j] += t;
                    b[i] += t;
                }
                if(!flag) break;
            }

            for(int i = 1; i < 8; i++) {
                if(a[i] != h[i] || b[i] != v[i]) {
                    flag = false;
                    break;
                }
            }

            if(flag) {
                n = hi;
                for(int i = 0; i < 8; i++) {
                    cout << "-.+"[n%3] << " ";
                    n /= 3;
                }
                cout << "\n";

                n = vj;
                for(int i = 1; i < 8; i++) {
                    cout << "-.+"[n%3] << " ";
                    n /= 3;
                    for(int j = 1; j < 8; j++) {
                        int t = h[j] + v[i] - A[i][j];
                        cout << "-.+"[t+1] << " ";
                    }
                    cout << "\n";
                }

                return 0;
            }
        }
    }

    assert(0);
}