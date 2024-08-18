#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

const int MAXN = 200005;
const int SQRTN = 400;

int N, d[MAXN], x[MAXN], dp[MAXN], psum[SQRTN+5][MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> d[i] >> x[i];
    }

    dp[1] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= SQRTN; j++) {
            if(i - j >= 0) {
                psum[j][i] += psum[j][i-j];
                psum[j][i] = (psum[j][i] % MOD + MOD) % MOD;
            }
            dp[i] += psum[j][i];
            dp[i] %= MOD;
        }
        if(d[i] > SQRTN) {
            for(int j = 1; j <= x[i]; j++) {
                if(i + d[i] * j > N) break;
                dp[i+d[i]*j] = (dp[i] + dp[i+d[i]*j]) % MOD;
            }
        } else {
            if(d[i] == 0) continue;
            if(i + d[i] > N) continue;
            psum[d[i]][i] += dp[i];
            psum[d[i]][i] %= MOD;
            psum[d[i]][i + d[i] * (min((N-i)/d[i], x[i])+1)] += MOD - dp[i];
            psum[d[i]][i + d[i] * (min((N-i)/d[i], x[i])+1)] %= MOD;
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; i++) {
        ans = (ans + dp[i]) % MOD;
    }
    cout << ans;
}