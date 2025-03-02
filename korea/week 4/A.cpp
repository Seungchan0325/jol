#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

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

int N, C, x[MAXN], y[MAXN];

int main()
{
    cin >> N >> C;
    for(int i = 0; i < N; i++) {
        cin >> x[i] >> y[i];
    }
    vector<tuple<int, int, int>> v;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            v.emplace_back((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]), i, j);
        }
    }
    sort(v.begin(), v.end());
    DSU dsu;
    dsu.init(N);
    int cnt = 0;
    long long ans = 0;
    for(auto [w, a, b] : v) {
        if(w >= C && dsu.find(a) != dsu.find(b)) {
            dsu.merge(a, b);
            ans += w;
            cnt++;
        }
    }

    if(cnt == N-1) cout << ans << "\n";
    else cout << "-1\n";
}