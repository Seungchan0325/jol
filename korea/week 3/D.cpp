#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 500505;

int N, K, chk[MAXN];
ll DP1[MAXN], DP2[MAXN], ans[MAXN];
vector<pair<int, ll>> g[MAXN];

void dfs1(int u, int p)
{
    if(chk[u]) DP2[u] = 1;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dfs1(v, u);
        DP1[u] += DP1[v] + DP2[v] * w;
        DP2[u] += DP2[v];
    }
}

void dfs2(int u, int p, int pdp1, int pdp2)
{
    ll dp1 = pdp1;
    ll dp2 = pdp2;
    if(chk[u]) dp2++;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dp1 += DP1[v] + w * DP2[v];
        dp2 += DP2[v];
    }
    for(auto [v, w] : g[u]) {
        if(v == p) continue;;
        int npdp1 = dp1;
        int npdp2 = dp2;
        npdp1 -= DP1[v] + w * DP2[v];
        npdp2 -= DP2[v];
        npdp1 += w * npdp2;
        dfs2(v, u, npdp1, npdp2);
    }
    ans[u] = dp1;
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    for(int i = 0; i < K; i++) {
        int u;
        cin >> u;
        chk[u] = true;
    }
    dfs1(1, -1);
    dfs2(1, -1, 0, 0);
    for(int i = 1; i <= N; i++) {
        cout << ans[i] << "\n";
    }
}