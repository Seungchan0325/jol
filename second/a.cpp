#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1000005;

ll N, T, a[MAXN], psum[MAXN];

int main()
{
    cin >> N >> T;
    vector<ll> v;
    for(ll i = 0; i < N; i++) {
        ll a;
        cin >> a;
        v.push_back(a%T);
        v.push_back(a%T+T);
    }

    sort(v.begin(), v.end());

    ll ans = 1e18;
    for(int i = 0; i < N; i++) {
        ll mid = (v[i] + v[i+N-1]) / 2;
        ans = min(ans, max(mid - v[i], v[i+N-1] - mid));
        mid = (v[i] + v[i+N-1] + 1) / 2;
        ans = min(ans, max(mid - v[i], v[i+N-1] - mid));
    }
    cout << ans;
}