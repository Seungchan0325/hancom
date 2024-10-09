#include <bits/stdc++.h>

using namespace std;

const int MAXN = 35;

int N, A[MAXN], B[MAXN];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    
    int idx = 0;
    for(int i = 0; i < N-1; i++) {
        B[idx] = A[i];
        idx += A[i];
        idx %= N;
        while(B[idx]) {
            idx = (idx + 1) % N;
        }
    }
    B[idx] = A[N-1];
    cout << N << "\n";
    for(int i = 0; i < N; i++) cout << B[i] << " ";
}