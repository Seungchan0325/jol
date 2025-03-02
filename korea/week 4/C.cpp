#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1010;
const ll INF = 1e18;

ll N, M, C, A[MAXN], cache[MAXN][MAXN];
vector<int> g[MAXN];

ll dp(int now, int path)
{
    if(path == 0) {
        if(now == 1) return 0;
        else return -INF;
    }
    ll& ret = cache[now][path];
    if(ret != -1) return ret;
    ret = -INF;
    for(auto nxt : g[now]) {
        ret = max(ret, dp(nxt, path-1) + A[nxt]);
    }
    return ret;
}

int main()
{
    cin >> N >> M >> C;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    memset(cache, -1, sizeof(cache));
    ll ans = 0;
    for(int path = 0; path <= 1005; path++) {
        ans = max(ans, A[1] + dp(1, path) - (ll)C * path * path);
    }
    cout << ans;
}