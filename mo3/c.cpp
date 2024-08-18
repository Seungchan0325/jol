#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using ii = pair<ll, ll>;
using tiii = tuple<ll, ll, ll>;

const int MAXN = 505;
const int MOD = 1e9 + 7;

ll N, a[MAXN], b[MAXN], DP[MAXN][MAXN], psum[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> a[i];
    for(int i = 1; i <= N; i++) cin >> b[i];

    DP[0][0] = 1;
    for(int n = 1; n <= N; n++) {
        for(int m = 1; m <= N; m++) {
            ll s1 = 0;
            for(int i = n; i >= 1; i--) {
                s1 += a[i];
                ll s2 = 0;
                for(int j = m; j >= 1; j--) {
                    s2 += b[j];
                    if(s1 * (m - j + 1) <= s2 * (n - i + 1)) {
                        DP[n][m] = (DP[n][m] + DP[i-1][j-1]) % MOD;
                    }
                }
            }
        }
    }

    for(int n = 1; n <= N; n++) {
        for(int m = 1; m <= N; m++) {
            ll s1 = 0;
            vector<ii> v;
            for(int j = m; j >= 1; j--) {
                s1 += b[j];
                v.emplace_back(s1, j);
            }

            sort(v.begin(), v.end(), [m](ii a, ii b) {
                return (m - b.second + 1) * a.first < (m - a.second + 1) * b.first;
            });

            ll s2 = 0;
            for(int i = n; i >= 1; i--) {
                s2 += a[i];

            }
        }
    }

    cout << DP[N][N];
}