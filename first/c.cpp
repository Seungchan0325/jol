#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;
const ll LOGN = 20;

ll N, M, sparse[2*MAXN][LOGN+5];

int main()
{
    vector<pair<ll, ll>> vv;
    cin >> N >> M;
    for(ll i = 0; i < N; i++) {
        ll s, e;
        cin >> s >> e;
        if(e < s) s -= M;
        vv.emplace_back(s, e);
        vv.emplace_back(s+M, e+M);
    }

    sort(vv.begin(), vv.end());
    ll lst = -M;
    vector<pair<ll, ll>> v;
    v.emplace_back(-M, -M);
    for(ll i = 0; i < vv.size(); i++) {
        if(lst < vv[i].second) {
            v.push_back(vv[i]);
            lst = vv[i].second;
        }
    }

    lst = 0;
    ll mx = -M, mxi = -1;
    for(ll i = 1; i < v.size(); i++) {
        while(lst < v.size() && v[lst].first <= v[i].second) {
            if(mx < v[lst].second) {
                mx = v[lst].second;
                mxi = lst;
            }
            lst++;
        }

        if(mxi == i) sparse[i][0] = 0;
        else sparse[i][0] = mxi;
    }

    for(ll i = v.size()-1; i > 0; i--) {
        for(ll j = 1; j <= LOGN; j++) {
            sparse[i][j] = sparse[sparse[i][j-1]][j-1];
        }
    }

    ll ans = 1e9;
    for(ll i = 1; i < v.size(); i++) {
        ll cnt = 2;
        ll u = i;
        for(ll j = LOGN; j >= 0; j--) {
            if(sparse[u][j] && v[sparse[u][j]].second < v[i].first + M) {
                cnt += (1<<j);
                u = sparse[u][j];
            }
        }

        if(sparse[u][0] && v[i].first + M <= v[sparse[u][0]].second) {
            ans = min(ans, cnt);
        }
    }

    if(ans >= 1e9) cout << -1;
    else cout << ans;
}