#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

bool chk[MAXN];
ll N, a[MAXN], root[MAXN], sum[MAXN], queries[MAXN], ans[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

ll merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return 0;
    root[y] = x;
    sum[x] += sum[y];
    return sum[x];
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> a[i];
        sum[i] = a[i];
    }
    for(int i = 1; i <= N; i++) cin >> queries[i];
    iota(root, root + N + 1, 0);
    ll mx = 0;
    for(int i = N; i >= 1; i--) {
        ans[i] = mx;

        int idx = queries[i];
        mx = max(mx, a[idx]);
        if(1 < idx && chk[idx-1]) {
            mx = max(mx, merge(idx-1, idx));
        }
        if(idx < N && chk[idx+1]) {
            mx = max(mx, merge(idx+1, idx));
        }
        chk[idx] = true;
    }

    for(int i = 1; i <= N; i++) cout << ans[i] << "\n";
}