#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const ll MAXN = 500005;

struct T {
    ll zero;
    ll sum;
    ll sz;
};

T tree[4*MAXN];
ll N, a[MAXN], b[MAXN], mypow[MAXN];

T merge(T a, T b)
{
    T ret;
    ret.sz = a.sz + b.sz;
    
    ret.sum = 0;
    ret.sum += a.sum * b.zero;
    ret.sum %= MOD;

    ret.sum += mypow[a.sz] * b.sum;
    ret.sum %= MOD;

    ret.zero = a.zero * b.zero;
    ret.zero %= MOD;
    return ret;
}

void update(ll pos, T v, ll s = 1, ll e = N, ll idx = 1)
{
    if(e < pos || pos < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    ll m = (s + e) / 2;
    update(pos, v, s, m, 2*idx);
    update(pos, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<ll> v;
    for(ll i = 1; i <= N; i++) { cin >> a[i]; v.push_back(a[i]); }
    for(ll i = 1; i <= N; i++) { cin >> b[i]; v.push_back(b[i]); }

    mypow[0] = 1;
    for(ll i = 1; i <= N; i++) mypow[i] = 2 * mypow[i-1] % MOD;

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<vector<tuple<ll, ll>>> updates(v.size());
    for(ll i = 1; i <= N; i++) {
        if(a[i] > b[i]) swap(a[i], b[i]);

        ll idx = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
        updates[idx].emplace_back(i, 2);

        idx = lower_bound(v.begin(), v.end(), b[i]) - v.begin();
        updates[idx].emplace_back(i, 1);
    }

    for(ll i = 1; i <= N; i++) update(i, {2, 0, 1});

    ll sum1 = 0;
    for(ll i = v.size()-1; i >= 0; i--) {
        for(auto [pos, cnt] : updates[i]) update(pos, T{2 - cnt, cnt * (pos + 1), 1});

        ll t;
        if(i == 0) t = v[i];
        else t = v[i] - v[i-1];

        sum1 += tree[1].sum * t % MOD;
        sum1 %= MOD;
    }

    for(ll i = 1; i <= N; i++) update(i, T{2, 0, 1});

    ll sum2 = 0;
    for(ll i = v.size()-1; i >= 0; i--) {
        for(auto [pos, cnt] : updates[i]) update(N - pos + 1, T{2 - cnt, cnt * pos, 1});

        ll t;
        if(i == 0) t = v[i];
        else t = v[i] - v[i-1];

        sum2 += tree[1].sum * t % MOD;
        sum2 %= MOD;
    }

    ll sum4 = 0;
    for(ll i = 1; i <= N; i++) {
        sum4 += a[i] + b[i];
        sum4 %= MOD;
    }

    sum4 *= mypow[N-1];
    sum4 %= MOD;

    ll result = ((sum1 - sum2 - sum4) % MOD + MOD) % MOD;
    cout << result;
}