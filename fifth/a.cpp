#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

ll N, A, B, C, sum[MAXN];
string S;

int main()
{
    cin >> N;
    cin >> S;
    cin >> A >> B >> C;

    ll ans = min(A, B) * N;

    ll b = 0;
    ll mn = 0;
    for(ll i = 0; i + 2 < N; i+=3) {
        int c = 0;
        if(S[i] != 'R') c++;
        if(S[(i+1)] != 'G') c++;
        if(S[(i+2)] != 'B') c++;

        mn += c * C;
        mn = min(mn, i * A + c * C);

        ll cost = mn + (N - i - 3) * B;
        ans = min(cost, ans);
    }

    b = 0;
    mn = A;
    for(ll i = 1; i + 2 < N; i+=3) {
        int c = 0;
        if(S[i] != 'R') c++;
        if(S[(i+1)] != 'G') c++;
        if(S[(i+2)] != 'B') c++;

        mn += c * C;
        mn = min(mn, i * A + c * C);

        ll cost = mn + (N - i - 3) * B;
        ans = min(cost, ans);
    }

    b = 0;
    mn = A+A;
    for(ll i = 2; i + 2 < N; i+=3) {
        int c = 0;
        if(S[i] != 'R') c++;
        if(S[(i+1)] != 'G') c++;
        if(S[(i+2)] != 'B') c++;

        mn += c * C;
        mn = min(mn, i * A + c * C);

        ll cost = mn + (N - i - 3) * B;
        ans = min(cost, ans);
    }

    cout << ans;
}