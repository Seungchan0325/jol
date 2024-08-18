#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int N, Q, A[MAXN];

struct Node {
    int l, r, data;
};

int last = 1, root[MAXN];
Node nd[(int)1e7];

void build(int node, int start, int end) {
    nd[node].data = 0;
    if(start == end) return;
    int mid = (start + end) / 2;
    build(nd[node].l = last++, start, mid);
    build(nd[node].r = last++, mid+1, end);
}

void update(int prv, int node, int start, int end, int pos, int delta) {
    if(start == end) {
        nd[node].data = nd[prv].data + delta;
        return;
    }

    int mid = (start + end) / 2;
    if(pos <= mid) {
        nd[node].l = last++; nd[node].r = nd[prv].r;
        update(nd[prv].l, nd[node].l, start, mid, pos, delta);
    } else {
        nd[node].l = nd[prv].l; nd[node].r = last++;
        update(nd[prv].r, nd[node].r, mid+1, end, pos, delta);
    }

    nd[node].data = nd[nd[node].l].data + nd[nd[node].r].data;
}

int query(int node, int start, int end, int left, int right) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return nd[node].data;

    int mid = (start + end) / 2;
    return query(nd[node].l, start, mid, left, right) + query(nd[node].r, mid+1, end, left, right);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) cin >> A[i];

    build(root[0] = 0, 0, MAXN);
    for(int i = 1; i <= N; i++) {
        update(root[i-1], root[i] = last++, 0, MAXN, A[i], 1);
    }

    while(Q--) {
        int l, r;
        cin >> l >> r;

        int lo = 0;
        int hi = r - l + 2;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            int cnt = query(root[r], 0, MAXN, mid, MAXN);
            cnt -= query(root[l-1], 0, MAXN, mid, MAXN);
            if(cnt >= mid) lo = mid;
            else hi = mid;
        }

        cout << lo << "\n";
    }
}