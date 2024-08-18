#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1005;
const ll MAXM = 505;

const ll INF = 1e18;

ll N, M, A[MAXN], DP[MAXN][MAXM];

int main()
{
    cin >> N >> M;
    for(ll i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for(ll i = 0; i <= N; i++) {
        for(ll j = 0; j <= M; j++) DP[i][j] = -INF;
    }
    DP[0][0] = 1;
    for(ll i = 0; i < N; i++) {
        for(ll j = 0; j <= M; j++) {
            DP[i+1][j+1] = max(DP[i+1][j+1], DP[i][j] + A[i+1]);
            DP[i+2][j+1] = max(DP[i+2][j+1], DP[i][j]/2 + A[i+2]);
        }
    }

    ll mx = -1;
    for(ll i = 0; i <= N; i++) {
        for(ll j = 0; j <= M; j++) {
            mx = max(mx, DP[i][j]);
        }
    }

    cout << mx;
}