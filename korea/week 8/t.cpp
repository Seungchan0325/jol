#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const int SQRTN = 0;

int N, A[MAXN], S[MAXN], sz, tree[MAXN];
vector<int> g[MAXN];
random_device rd;
mt19937 gen(rd());

void update(int x, int v)
{
    while(x <= N) {
        tree[x] += v;
        x += x&-x;
    }
}

int query(int x)
{
    int ret = 0;
    while(x > 0) {
        ret += tree[x];
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
        g[idx].push_back(i);
    }

    long long ans = 0;

    // for(int i = 1; i <= N; i++) {
    //     for(int j = i; j <= N && j - i + 1 <= 2*SQRTN; j++) {
    //         for(int iter = 0; iter < 100; iter++) {
    //             int k = uniform_int_distribution<int>(i, j)(gen);
    //             int c = lower_bound(v.begin(), v.end(), A[i]) - v.begin();
    //             if(g[c].size() >= SQRTN) continue;
    //             int cnt = upper_bound(g[c].begin(), g[c].end(), j) - lower_bound(g[c].begin(), g[c].end(), i);
    //             if(2*cnt > j - i + 1) {
    //                 ans++;
    //                 break;
    //             }
    //         }
    //     }
    // }

    for(int i = 0; i < v.size(); i++) {
        int sz = g[i].size();
        if(sz >= SQRTN) {
            for(int j = 1; j <= N; j++) S[j] = tree[j] = 0;
            for(auto j : g[i]) S[j]++;
            for(int j = 1; j <= N; j++) S[j] += S[j-1];
            vector<int> a;
            for(int j = 0; j <= N; j++) a.push_back(2*S[j] - j);
            sort(a.begin(), a.end());
            a.erase(unique(a.begin(), a.end()), a.end());
            for(int j = 0; j <= N; j++) {
                int idx = lower_bound(a.begin(), a.end(), 2*S[j]-j) - a.begin() + 1;
                ans += query(idx - 1);
                update(idx, 1);
            }
        }
    }

    cout << ans;
}