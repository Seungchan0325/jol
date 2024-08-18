#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 505;

ll n, m, value[MAXN], root[MAXN];
bool visited[MAXN];
vector<pair<ll, ll>> graph[MAXN];
vector<tuple<ll, ll, ll>> edges;

bool dfs(ll u, ll x)
{
    visited[u] = true;
    value[u] = x;
    bool ret = true;
    if(x <= 0 || x >= 2000) ret = false;

    for(auto [v, w] : graph[u]) {
        if(visited[v]) {
            if(value[v] + value[u] != w) {
                ret = false;
            }
        } else {
            if(!dfs(v, w - x)) {
                ret = false;
            }
        }
    }

    return ret;
}

void dfs2(int u)
{
    visited[u] = false;
    for(auto [v, w] : graph[u]) {
        if(visited[v]) dfs2(v);
    }
}

void dfs3(int u)
{
    visited[u] = true;
    for(auto [v, w] : graph[u]) {
        if(!visited[v]) dfs3(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
        edges.emplace_back(u, v, w);
    }

    vector<int> v;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            v.push_back(i);
            dfs3(i);
        }
    }

    memset(visited, 0, sizeof(visited));
    for(ll i = 1; i < 2000; i++) {
        for(auto u : v) {
            if(!visited[u] && !dfs(u, i)) {
                dfs2(u);
            }
        }
    }

    for(ll i = 0; i < n; i++) {
        if(visited[i]) cout << value[i] << " ";
        else cout << "1 ";
    }
}