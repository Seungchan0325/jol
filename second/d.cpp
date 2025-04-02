#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int MAXA = 1010101;

using ll = long long;

template<typename T = int64_t, size_t sz = 17, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}

	void Update(int i, T val) {
		--i |= 1 << sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(int l, int r) {
		T L = t, R = t; --l |= 1 << sz, --r |= 1 << sz;
		while (l <= r) {
			if (l & 1) L = f(L, tree[l++]);
			if (~r & 1) R = f(tree[r--], R);
			l >>= 1, r >>= 1;
		}
		return f(L, R);
	}
};

struct LCMGCDNode {
    LCMGCDNode() : a(0), b(0), c(0) {}
    LCMGCDNode(ll v) : a(v), b(0), c(0) {}
    ll a, b, c;
};

struct LCMGCD {
    void push(LCMGCDNode& _a, ll x)
    {
        auto& [a, b, c] = _a;
        c = gcd(c, lcm(lcm(b, a), x));
        b = gcd(b, lcm(a, x));
        a = gcd(a, x);
    }
    LCMGCDNode operator () (LCMGCDNode& a, LCMGCDNode& b)
    {
        auto ret = a;
        push(ret, b.a);
        push(ret, b.b);
        push(ret, b.c);
        return ret;
    }
};

using LCMGCDSeg = SegTree<LCMGCDNode, 17, LCMGCD>;

int N, Q, A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;

    LCMGCDSeg sg;
    for(int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        sg.Update(i, LCMGCDNode(a));
    }

    while(Q--) {
        char op;
        cin >> op;
        if(op == 'Q') {
            int l, r, k;
            cin >> l >> r >> k;
            auto ans = sg.Query(l, r);
            if(k == 0) cout << ans.a << "\n";
            if(k == 1) cout << ans.b << "\n";
            if(k == 2) cout << ans.c << "\n";
        } else if(op == 'U') {
            int j, x;
            cin >> j >> x;
            sg.Update(j, LCMGCDNode(x));
        } else {
            assert(0);
        }
    }
}