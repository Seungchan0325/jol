#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using ll = long long;

const ll MAXN = 300005;

ll N, M, K, c[MAXN];
ll dp[400][MAXN], fac[6], per[6][6], toidx[1000000];
vector<ll> graph[MAXN];
vector<vector<ll>> pper;
bool chk[6];

ll to_idx(const vector<ll>& p)
{
    ll idx = 0;
    for(ll i = 0; i < p.size(); i++) {
        idx *= K+1;
        idx += p[i];
    }

    return toidx[idx];
}

void gen_per(vector<ll> p)
{
    if(p.size() >= 1) {
        pper.push_back(p);
        ll idx = 0;
        for(ll i = 0; i < p.size(); i++) {
            idx *= K+1;
            idx += p[i];
        }
        toidx[idx] = pper.size() - 1;
    }
    for(ll i = 1; i <= K; i++) {
        if(chk[i]) continue;
        p.push_back(i);
        chk[i] = true;
        gen_per(p);
        chk[i] = false;
        p.pop_back();
    }
}

int main()
{
    cin >> N >> M >> K;
    for(ll i = 1; i <= N; i++) cin >> c[i];
    for(ll i = 0; i < M; i++) {
        ll u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    fac[0] = 1;
    fac[1] = 1;
    for(ll i = 2; i <= 5; i++) {
        fac[i] = fac[i-1] * i;
    }

    for(ll n = 1; n <= 5; n++) {
        for(ll r = 1; r <= n; r++) {
            per[n][r] = fac[n] / fac[n - r];
        }
    }
    gen_per({});

    for(ll u = 1; u <= N; u++) {
        ll idx = to_idx({c[u]});
        dp[idx][u] = 1;
    }

    ll sum = 0;
    for(const auto& p : pper) {
        if(p.size() < 2) continue;
        ll idx = to_idx(p);
        assert(pper[idx] == p);
        ll prv = to_idx(vector<ll>(p.begin(), p.end()-1));
        assert(pper[prv] == vector<ll>(p.begin(), p.end()-1));
        for(ll u = 1; u <= N; u++) {
            if(c[u] != p.back()) continue;
            for(auto v : graph[u]) {
                dp[idx][u] += dp[prv][v];
            }
            sum += dp[idx][u];
        }
    }
    cout << sum;
}