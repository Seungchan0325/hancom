#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

int N, K, indeg[MAXN], P[MAXN], root[MAXN], sz[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);

    if(x == y) return;

    root[y] = x;
    sz[x] += sz[y];
}

void mmeerrggee(int u)
{
    merge(P[u], u);
    if(indeg[P[u]] == 1) mmeerrggee(P[u]);
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i < N; i++) {
        cin >> P[i];
        indeg[P[i]]++;
    }

    for(int i = 0; i < N; i++) {
        if(indeg[i] == 0) {
            mmeerrggee(i);
        }
    }

    
}