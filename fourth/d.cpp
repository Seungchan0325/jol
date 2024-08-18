#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 500005;

ll N, Q, D, A[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    cin >> Q >> D;

    sort(A + 1, A + N + 1);
    ll lst = A[N] + D * (N - 1);
    ll prv = A[N] - 1 + A[N] - A[1] + 1 - N;

    A[N+1] = 1e18;

    while(Q--) {
        ll x;
        cin >> x;

        ll result = 0;
        if(x < A[1]) {
            result = x;
        } else {
            ll d = 0;
            int idx = upper_bound(&A[1], &A[N+1], x) - &A[0];
            while(d < D) {
                ll td = (A[idx] - x - 1) / (idx - 1);
                if(d + td > D) {
                    td = D - d;
                }
                d += td;
                x += (idx - 1) * td;
                idx++;
            }
        }
        cout << x << "\n";
    }
}