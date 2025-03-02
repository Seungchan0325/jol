#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2020202;

struct DSU {
    vector<int> root;
    void init(int n)
    {
        root.resize(n);
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

bool chk[MAXN];
int N, M, atk[MAXN], ans[MAXN];
vector<int> g[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= N; i++) {
        cin >> atk[i];
    }
    for(int i = 1; i <= N; i++) chk[i] = true;
    int component = 0;
    DSU dsu;
    dsu.init(N+1);
    for(int i = N; i >= 1; i--) {
        chk[atk[i]] = false;
        component += 1;
        for(auto neighbor : g[atk[i]]) {
            if(!chk[neighbor] && dsu.find(atk[i]) != dsu.find(neighbor)) {
                dsu.merge(neighbor, atk[i]);
                component--;
            }
        }
        ans[i] = component;
    }
    for(int i = 1; i <= N; i++) {
        if(ans[i] == 1) cout << "YES\n";
        else cout << "NO\n";
    }
}