#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10101;
const int LOGN = 14;

int N, sparse[MAXN][LOGN+1], depth[MAXN], indeg[MAXN];
vector<int> g[MAXN];

void dfs(int u, int p)
{
    for(int i = 1; i <= LOGN; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    }
    for(auto v : g[u]) {
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        sparse[v][0] = u;
        dfs(v, u);
    }
}

int lca(int u, int v)
{
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int i = 0; i <= LOGN; i++) {
        if(diff&(1<<i)) {
            u = sparse[u][i];
        }
    }

    if(u == v) return u;

    for(int i = LOGN; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }
    
    return sparse[u][0];
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }

    for(int i = 1; i <= N; i++) {
        if(indeg[i] == 0)
            dfs(i, -1);
    }

    int u, v;
    cin >> u >> v;
    cout << lca(u, v);
}