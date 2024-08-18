#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

ll N, area[MAXN][3];

int main()
{
    cin >> N;

    ll sum = 0;
    for(int i = 0; i < 2*N; i++) {
        ll x, y;
        cin >> x >> y;

        ll tx = max(min(x, N), 1LL);
        ll ty = max(min(y, 2LL), 1LL);
        sum += abs(tx - x);
        sum += abs(ty - y);

        area[tx][ty]++;
    }

    for(int x = 1; x <= N; x++) {
        area[x][1]--;
        area[x][2]--;
    }

    for(int x = 1; x <= N; x++) {
        if(area[x][1] * area[x][2] < 0) {
            if(abs(area[x][1]) < abs(area[x][2])) {
                sum += abs(area[x][1]);
                area[x][2] += area[x][1];
                area[x][1] = 0;
            } else {
                sum += abs(area[x][2]);
                area[x][1] += area[x][2];
                area[x][2] = 0;
            }
        }

        if(x < N) {
            sum += abs(area[x][1]) + abs(area[x][2]);
            area[x+1][1] += area[x][1];
            area[x+1][2] += area[x][2];
        }
    }

    cout << sum;
}