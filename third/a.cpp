#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505;

ll R, C, a, bp, psum[MAXN][MAXN];

ll Sum(int t, int b, int l, int r)
{
    return psum[b][r] - psum[t-1][r] - psum[b][l-1] + psum[t-1][l-1];
}

int main()
{
    cin >> R >> C >> a >> bp;
    if(a > bp) swap(a, bp);
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            cin >> psum[r][c];
        }
    }

    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            psum[r][c] += psum[r][c-1] + psum[r-1][c] - psum[r-1][c-1];
        }
    }

    ll mid = (a + bp + 1) / 2;
    ll ans = 1e18;
    for(int t = 1; t <= R; t++) {
        for(int b = t; b <= R; b++) {
            int hi = 1;
            for(int lo = 1; lo <= C; lo++) {
                while(hi < lo || (hi < C && abs(Sum(t, b, lo, hi) - a) + abs(Sum(t, b, lo, hi) - bp) > abs(Sum(t, b, lo, hi+1) - a) + abs(Sum(t, b, lo, hi+1) - bp))) {
                    hi++;
                }
                ll sum = Sum(t, b, lo, hi);
                ans = min(ans, abs(sum - a) + abs(sum - bp));
            }
        }
    }
    cout << ans;
}