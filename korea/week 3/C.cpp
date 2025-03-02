#include <bits/stdc++.h>

using namespace std;

const int MAXN = 201010;
const int MOD = 1e9 + 7;

int N, M, C, A[MAXN], in[MAXN], out[MAXN], rin[MAXN], pv;
vector<int> g[MAXN];

vector<int> tree[4*MAXN];

void init(int s, int e, int idx)
{
    if(s == e) {
        tree[idx].push_back(A[rin[s]]);
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx].resize(e - s + 1);
    merge(tree[2*idx].begin(), tree[2*idx].end(),
          tree[2*idx+1].begin(), tree[2*idx+1].end(),
          tree[idx].begin());
}

int query(int l, int r, int c, int s = 1, int e = N, int idx = 1)
{
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return upper_bound(tree[idx].begin(), tree[idx].end(), c) - tree[idx].begin();
    int m = (s + e) / 2;
    return query(l, r, c, s, m, 2*idx) + query(l, r, c, m+1, e, 2*idx+1);
}

void dfs(int u, int p)
{
    in[u] = ++pv;
    rin[in[u]] = u;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
    }
    out[u] = pv;
}

int main()
{
    cin >> N >> M >> C;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1);
    init(1, N, 1);
    int ans = 0;
    for(int i = 1; i <= M; i++) {
        int u, c;
        cin >> u >> c;
        ans += query(in[u], out[u], c);
        ans %= MOD;
    }
    cout << ans;
}