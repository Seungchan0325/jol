#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

ll N, T, a, b, k[MAXN], psum[MAXN];

int main()
{
    cin >> N >> T >> a >> b;
    for(ll i = 1; i <= N; i++) {
        cin >> k[i];
        psum[i] = psum[i-1] + k[i];
    }

    ll ans = 0;
    for(ll i = 1; i <= N; i++) {
        ll m = a * i;
        if(m > T) continue;
        ll n = T - m;

        ll s = n / b;
        ll e = s + i;
        if(e > N) {
            ans = max(ans, psum[N] - psum[N-i]);
        } else {
            ans = max(ans, psum[e] - psum[s]);
        }
    }

    cout << ans;
}