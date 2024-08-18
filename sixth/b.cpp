#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

ll N, psum[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> psum[i];
    }

    sort(psum + 1, psum + N + 1, greater<>());

    for(int i = 1; i <= N; i++) {
        psum[i] += psum[i-1];
    }

    ll ans = 1e18;
    for(int i = 1; i <= N; i++) {
        ll sum = 3600LL * (i-1);
        ll lst = 0;
        for(ll w = 0; lst < N; w++) {
            if(w > 12) {
                sum = 1e18;
                break;
            }
            sum += (1LL<<w) * (psum[min(lst+i, N)] - psum[lst]);
            lst += i;
        }
        ans = min(ans, sum);
    }

    cout << ans;
}