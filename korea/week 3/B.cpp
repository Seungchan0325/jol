#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int LOGN = 17;

int N, sparse[MAXN][LOGN+1], mxsparse[MAXN][LOGN+1], mnsparse[MAXN][LOGN+1], depth[MAXN];
vector<pair<int, int>> g[MAXN];

void dfs(int u, int p)
{
    for(int i = 1; i <= LOGN; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
        mxsparse[u][i] = max(mxsparse[u][i-1], mxsparse[sparse[u][i-1]][i-1]);
        mnsparse[u][i] = min(mnsparse[u][i-1], mnsparse[sparse[u][i-1]][i-1]);
    }
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        sparse[v][0] = u;
        mxsparse[v][0] = w;
        mnsparse[v][0] = w;
        dfs(v, u);
    }
}

pair<int, int> lca(int u, int v)
{
    int mn = 1e9;
    int mx = -1e9;
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int i = 0; i <= LOGN; i++) {
        if(diff&(1<<i)) {
            mn = min(mn, mnsparse[u][i]);
            mx = max(mx, mxsparse[u][i]);
            u = sparse[u][i];
        }
    }

    if(u == v) return {mn, mx};

    for(int i = LOGN; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            mn = min(mn, mnsparse[u][i]);
            mx = max(mx, mxsparse[u][i]);
            mn = min(mn, mnsparse[v][i]);
            mx = max(mx, mxsparse[v][i]);
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }

    mn = min(mn, mnsparse[u][0]);
    mx = max(mx, mxsparse[u][0]);
    mn = min(mn, mnsparse[v][0]);
    mx = max(mx, mxsparse[v][0]);
    
    return {mn, mx};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    dfs(1, -1);

    int Q;
    cin >> Q;
    while(Q--) {
        int u, v;
        cin >> u >> v;
        auto [mn, mx] = lca(u, v);

        cout << mn << " " << mx << "\n";
    }
}