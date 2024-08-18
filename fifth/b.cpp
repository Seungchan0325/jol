#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll N, L, R;

int main()
{
    cin >> N >> L >> R;
    // assert(L == R);
    map<ll, ll> m1, m2;

    for(ll i = 0; i < N; i++) {
        ll x, d, w;
        cin >> x >> d >> w;
        if(x < 0) {
            if(d > 0) {
                m1[abs(x)] += w;
            } else {
                m1[2*L - abs(x) + 1] += w;
            }
        } else {
            if(d < 0) {
                m2[abs(x)] += w;
            } else {
                m2[2*R - abs(x) + 1] += w;
            }
        }
    }

    map<ll, priority_queue<ll>> m;

    ll G = gcd(2*L, 2*R);

    for(auto [idx, w] : m1) {
        m[idx%G].push(w);
    }

    for(auto [idx, w] : m2) {
        m[idx%G].push(w);
    }

    ll sum = 0;
    for(auto& [idx, pq] : m) {
        for(int i = 0; i < 2*R/G && pq.size(); i++) {
            sum += pq.top(); pq.pop();
        }
    }

    cout << sum;
}