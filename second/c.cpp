#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

bool visited[MAXN];
int N, M;
vector<int> graph[MAXN];
vector<int> ans;

int dfs(int u, int p)
{
    int ret = 0;
    visited[u] = true;
    for(auto v : graph[u]) {
        if(visited[v] && v != p) {
            ret++;
        }
    }
    assert(ret < 2);
    for(auto v : graph[u]) {
        if(v == p || visited[v]) continue;
        ret += dfs(v, u);
    }
    if(ret >= 2) {
        ans.push_back(u);
        return 0;
    } else {
        return ret;
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    visited[0] = true;
    for(auto v : graph[0]) {
        if(!visited[v] && dfs(v, 0)) {
            ans.push_back(v);
        }
    }

    cout << ans.size() << "\n";
    for(auto u : ans) cout << u << " ";
}