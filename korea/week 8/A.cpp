#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int BUCK = 300;

int sqrtN;

struct Query {
    int s, e, idx;
    bool operator < (const Query& other) const {
        if(s / sqrtN != other.s / sqrtN) return s  < other.s;
        return e < other.e;
    }
};

int N, Q, A[MAXN], c[MAXN], ans[MAXN], b[400][MAXN], mx[400];

void update(int x, int d)
{
    int idx = x / BUCK;
    b[idx][c[x]]--;
    c[x] += d;
    b[idx][c[x]]++;

    if(b[idx][mx[idx]+1]) mx[idx]++;
    if(!b[idx][mx[idx]]) mx[idx]--;
}

int main()  
{
    cin >> N >> Q;
    sqrtN = sqrt(N);
    vector<int> v;
    v.reserve(N);
    for(int i = 1; i <= N; i++) cin >> A[i], v.push_back(A[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 1; i <= N; i++) {
        A[i] = lower_bound(v.begin(), v.end(), A[i]) - v.begin();
    }

    for(int i = 0; i < v.size(); i++) b[i/BUCK][0]++;

    vector<Query> q(Q);
    for(int i = 0; i < Q; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].idx = i;
    }
    sort(q.begin(), q.end());
    int l = 1, r = 0;
    for(auto [s, e, idx] : q) {
        while(l < s) update(A[l++], -1);
        while(s < l) update(A[--l], 1);
        while(r < e) update(A[++r], 1);
        while(e < r) update(A[r--], -1);

        int mxi = 400-1;
        for(int i = 400-1; i >= 0; i--) {
            if(mx[mxi] < mx[i]) mxi = i;
        }
        for(int i = BUCK * (mxi + 1) - 1; ; i--) {
            if(c[i] == mx[mxi]) {
                ans[idx] = i;
                break;
            }
        }        
    }
    for(int i = 0; i < Q; i++) {
        cout << v[ans[i]] << "\n";
    }
}