#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

bool inStack[MAXN];
int N, M, indeg[MAXN], scc[MAXN], num[MAXN], low[MAXN], pv, t;
vector<int> g[MAXN];
stack<int> s;

void dfs(int u)
{
    num[u] = low[u] = ++pv;
    s.push(u);
    inStack[u] = true;

    for(auto v : g[u]) {
        if(!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if(low[u] == num[u]) {
        t++;
        while(s.top() != u) {
            scc[s.top()] = t;
            inStack[s.top()] = false;
            s.pop();
        }
        scc[s.top()] = t;
        inStack[s.top()] = false;
        s.pop();
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    for(int i = 1; i <= N; i++)
        if(!num[i])
            dfs(i);
    for(int i = 1; i <= N; i++) {
        for(auto v : g[i]) {
            if(scc[i] == scc[v]) continue;
            indeg[scc[v]]++;
        }
    }
    int cnt = 0;
    for(int i = 1; i <= t; i++) {
        if(indeg[i] == 0) {
            cnt++;
        }
    }
    cout << cnt;
}
