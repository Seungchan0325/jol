#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const int SQRTN = 800;

int N, A[MAXN], S[MAXN], t[4*MAXN], c[MAXN];
vector<int> g[MAXN];

void update(int x, int v)
{
    while(x <= 4*N) {
        t[x] += v;
        x += x&-x;
    }
}

int query(int x)
{
    int ret = 0;
    while(x > 0) {
        ret += t[x];
        x -= x&-x;
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<int> v;
    for(int i = 1; i <= N; i++) cin >> A[i], v.push_back(A[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 1; i <= N; i++) {
        int idx = lower_bound(v.begin(), v.end(), A[i]) - v.begin();
        A[i] = idx;
        g[idx].push_back(i);
    }

    long long ans = 0;
    int mxlen = 0;
    for(int i = 0; i < v.size(); i++) {
        if(g[i].size() < SQRTN) mxlen = max(mxlen, 2 * (int)g[i].size());
    }

    int mx = 0;
    for(int i = 1; i <= N; i++) {
        mx = 0;
        for(int j = i; j <= N && j - i + 1 <= mxlen; j++) {
            if(g[A[j]].size() < SQRTN) {
                mx = max(mx, ++c[A[j]]);
            }
            if(2 * mx > j - i + 1) {
                ans++;
            }
        }
        for(int j = i; j <= N && j - i + 1 <= mxlen; j++) {
            if(g[A[j]].size() < SQRTN)
                c[A[j]]--;
        }
    }

    for(int i = 0; i < v.size(); i++) {
        if(g[i].size() >= SQRTN) {
            for(int j = 1; j <= N; j++) S[j] = 0;
            for(auto j : g[i]) S[j]++;
            for(int j = 1; j <= N; j++) S[j] += S[j-1];

            int mn = 0;
            for(int j = 0; j <= N; j++) mn = min(mn, 2*S[j]-j);
            for(int j = 0; j <= N; j++) {
                ans += query(2*S[j]-j-mn);
                update(2*S[j]-j-mn+1, 1);
            }
            
            for(int j = 0; j <= N; j++) {
                update(2*S[j]-j-mn+1, -1);
            }
        }
    }

    cout << ans;
}