#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

bool moved[MAXN];
int N, M, A[MAXN], B[MAXN], ans[MAXN], lst[MAXN];

int f(int u)
{
    if(moved[u]) return 0;
    if(lst[B[u]] == 0) {
        moved[u] = true;
        lst[B[u]] = u;
        // lst[A[u]] = 0;
        return 1;
    }

    if(u < lst[B[u]]) {
        // lst[A[u]] = 0;
        int tmp = lst[B[u]];
        lst[B[u]] = u;
        int ret = f(tmp);
        moved[u] = true;
        return ret;
    }

    return 0;
}

int main()
{
    cin >> N >> M;
    assert(N < MAXN);
    assert(M < MAXN);
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> B[i];
        assert(A[i] != B[i]);
        assert(1 <= A[i] && A[i] <= M);
        assert(1 <= B[i] && B[i] <= M);
    }

    int cnt = 0;
    set<int> s;
    for(int i = N; i >= 1; i--) {
        if(lst[A[i]]) cnt += f(lst[A[i]]);
        else cnt++;
        lst[A[i]] = i;
        ans[i] = cnt;
    }

    for(int i = 1; i <= N; i++) cout << ans[i] << "\n";
}