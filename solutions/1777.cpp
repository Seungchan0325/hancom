#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int N, A[MAXN];

void range_swap(int lo, int hi)
{
    assert(lo <= hi);
    while(lo < hi) {
        swap(A[lo++], A[hi--]);
    }
}

int main()
{
    cin >> N;
    bool flag = true;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        if(A[i] != i) flag = false;
    }

    if(flag) {
        cout << "1 1\n1 1\n1 1\n";
        return 0;
    }

    vector<int> v;
    v.push_back(1);
    for(int i = 2; i < N; i++) {
        if(abs(A[i] - A[i-1]) > 1 || abs(A[i] - A[i+1]) > 1) {
            v.push_back(i);
        }
    }
    v.push_back(N);
    
    for(int l = 0; l < v.size(); l++) {
        for(int r = l+1; r < v.size(); r++) {
            range_swap(v[l], v[r]);
            bool flag = true;
            for(int k = 1; k <= N; k++) {
                if(A[k] != k) {
                    flag = false;
                }
            }
            if(flag) {
                cout << v[l] << " " << v[r] << "\n";
                cout << "1 1\n";
                cout << "1 1\n";
                return 0;
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
                            cout << v[l] << " " << v[r] << "\n";
                            cout << i << " " << j << "\n";
                            cout << s << " " << e << "\n";
                            return 0;
                        }

                        range_swap(s, e);
                    } else if(s == -1) {
                        cout << v[l] << " " << v[r] << "\n";
                        cout << i << " " << j << "\n";
                        cout << "1 1\n";
                        return 0;
                    }

                    range_swap(i, j);
                }
            }
            range_swap(v[l], v[r]);
        }
    }
}