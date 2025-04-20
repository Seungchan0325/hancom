#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 25050505;
const int S = (1<<8);

int A[MAXN], B[MAXN], C[S];

/// 배열 A와 원소의 개수 N을 전달받아 초기화한다.
void initUser(int nSize, int *arr) {
    for(int i = 0; i < nSize; i++) A[i] = arr[i]+(1LL<<31);

    int *ap = A, *bp = B;
    for(int i = 0; i < 32; i+=8) {
        for(int j = 0; j < S; j++) C[j] = 0;
        for(int j = 0; j < nSize; j++) C[(ap[j]>>i)&(S-1)]++;
        for(int j = 1; j < S; j++) C[j] += C[j-1];
        for(int j = nSize-1; j >= 0; j--) bp[--C[(ap[j]>>i)&(S-1)]] = ap[j];
        swap(ap, bp);
    }
}

/// " A 배열을 오름차순 정렬했을때 idx번째 값은 얼마인가? "
/// 라는 질의에 실시간으로 답하는 함수이다.
int query(int idx) {
    return A[idx-1]-(1LL<<31);
}
