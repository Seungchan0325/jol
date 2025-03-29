#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int MAXM = 303030;

typedef long long ll;
struct Node{
    Node *l, *r;
    ll v;
    Node(){ l = r = NULL; v = 0; }
};

//root[i] = i번째 세그먼트 트리의 루트
Node *root[MAXM]; //root[0] 할당 필수
int idx =0 ;

void build(Node *node, int s, int e){ //0번 트리 생성
    if(s == e){
        node->v = 0; return;
    }
    int m = s + e >> 1;
    node->l = new Node(); node->r = new Node();
    build(node->l, s, m); build(node->r, m+1, e);
    node->v = node->l->v + node->r->v;
}
void add(Node *prv, Node *now, int s, int e, int x, int v){
    if(s == e){
        now->v = v + prv->v; return;
    }
    int m = s + e >> 1;
    if(x <= m){ //왼쪽 자식에 업데이트 하는 경우
        //왼쪽 자식은 새로운 정점 생성, 오른쪽 자식은 재활용
        now->l = new Node(); now->r = prv->r;
        add(prv->l, now->l, s, m, x, v);
    }else{
        //오른쪽 자식은 새로운 정점 생송, 왼쪽 자식은 재활용
        now->l = prv->l; now->r = new Node();
        add(prv->r, now->r, m+1, e, x, v);
    }
    now->v = now->l->v + now->r->v;
}
ll query(Node *node, int s, int e, int l, int r){
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return node->v;
    int m = s + e >> 1;
    return query(node->l, s, m, l, r) + query(node->r, m+1, e, l, r);
}

bool vst[MAXN];
int sparse[MAXN][20], mnsparse[MAXN][20], dep[MAXN], mnmn[MAXN];
int ans, N, M, rin[MAXN], in[MAXN], out[MAXN], pv, par[MAXN], far[MAXN], near[MAXN], cnt[MAXN], ch_i[MAXN];
vector<pair<int, int>> edges;
vector<int> g[MAXN], t[MAXN], b[MAXN];
Node* tme[MAXN];

set<int> dfs0(int u, int p)
{
    mnmn[u] = 1e9;
    set<int> s;
    in[u] = ++pv;
    rin[in[u]] = u;
    vst[u] = true;
    
    for(auto v : g[u]) {
        if(vst[v]) {
            if(in[v] < in[u] && v != p) {
                root[idx] = new Node();
                add(root[idx-1], root[idx], 1, N, in[v], 1);
                idx++;
                mnmn[u] = min(mnmn[u], in[v]);
            }
            if(in[v] < in[u]) b[u].push_back(v);
            if(v != p) s.insert(in[v]);
            continue;
        }
    }
    tme[in[u]] = root[idx-1];
    for(auto v : g[u]) {
        if(vst[v]) {
            continue;
        }
        ch_i[v] = t[u].size();
        t[u].push_back(v);
        par[v] = u;
        dep[v] = dep[u] + 1;
        auto ch = dfs0(v, u);
        if(s.size() < ch.size()) swap(s, ch);
        s.insert(ch.begin(), ch.end());
    }
    while(s.size() && *s.rbegin() >= in[par[u]]) s.erase(*s.rbegin());
    if(s.size()) {
        far[u] = *s.begin();
        near[u] = *s.rbegin();
    } else {
        far[u] = N;
        near[u] = 0;
    }
    out[u] = pv;
    return s;
}

void build_lca()
{
    for(int i = 1; i <= N; i++) {
        sparse[i][0] = par[i];
        mnsparse[i][0] = min(mnmn[i], mnmn[par[i]]);
    }
    for(int i = 1; i < 20; i++)
        for(int j = 1; j <= N; j++) {
            sparse[j][i] = sparse[sparse[j][i-1]][i-1];
            mnsparse[j][i] = min(mnsparse[j][i-1], mnsparse[sparse[j][i-1]][i-1]);
        }
}

int lca(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    int ret = min(mnmn[u], mnmn[v]);
    for(int i = 0; i < 20; i++)
        if(diff & (1<<i)) {
            ret = min(ret, mnsparse[u][i]);
            u = sparse[u][i];
        }

    if(u == v) return ret;
    for(int i = 19; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            ret = min(ret, mnsparse[u][i]);
            ret = min(ret, mnsparse[v][i]);
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }
    ret = min(ret, mnsparse[u][0]);
    return ret;
}

int main()
{
    // freopen("/home/seungchan1e/jol/third/mostovi/43.in", "r", stdin);
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        edges.emplace_back(u, v);
    }

    tme[0] = root[idx++] = new Node();
    build(root[0], 1, N);

    dfs0(1, -1);
    build_lca();
    // cout << "-------\n";
    for(int i = 1; i <= N; i++) {
        for(auto j : t[i]) {
            if(far[j] < in[i]) cnt[i]++;
        }
    }

    vector<pair<int, int>> anss;
    for(int i = 1; i <= N; i++) {
        int sum = t[i].size();
        int pos = t[i].size();
        vector<int> c(t[i].size(), 1);
        vector<pair<int, int>> up, mid;
        for(auto j : t[i]) up.emplace_back(far[j], j), mid.emplace_back(near[j], j);
        sort(up.begin(), up.end());
        sort(mid.begin(), mid.end());
        sort(b[i].begin(), b[i].end(), [](int i, int j){return in[i] < in[j];});
        int p, q, m, tptp;
        p = q = 0;
        for(int j : b[i]) {
            while(p < up.size() && up[p].first < in[j]) {
                if(c[ch_i[up[p].second]]++ == 0) pos++;
                sum++;
                p++;
            }
            while(q < mid.size() && mid[q].first <= in[j]) {
                if(--c[ch_i[mid[q].second]] == 0) pos--;
                sum--;
                q++;
            }
            if(t[i].size()) {
                if(j != 1 && par[i] != j && pos != t[i].size()) {
                    ans++;
                    goto CONTINUE;
                    continue;
                }
                if(j != 1 && par[i] == j && p < t[i].size()) {
                    ans++;
                    goto CONTINUE;
                    continue;
                }
                if(j == 1 && par[i] != j && q) {
                    ans++;
                    goto CONTINUE;
                    continue;
                }
                if(j == 1 && par[i] == j && (t[i].size() >= 2 || t[1].size() >= 2)) {
                    ans++;
                    goto CONTINUE;
                    continue;
                }
            }
            {
                int lo = 0;
                int hi = t[j].size();
                while(lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    if(in[t[j][mid]] <= in[i]) lo = mid;
                    else hi = mid;
                }
                m = t[j][lo];
            }
            // side to top
            if(!(j == 1 || cnt[j] - (far[m] < in[j] ? 1 : 0) >= (int)t[j].size() - 1)) {
                ans++;
                goto CONTINUE;
                continue;
            }

            if(j == 1 && t[j].size() >= 2 && par[i] != j) {
                ans++;
                goto CONTINUE;
                continue;
            }

            if(j == 1 && t[j].size() >= 3) {
                ans++;
                goto CONTINUE;
                continue;
            }
            
            tptp = lca(m, par[i]);//정신이 나가럴아ㅣㅁ;ㅇ
            // mid to top or (s to top)
            {
                int ttt = query(tme[out[m]], 1, N, in[1], in[par[j]]) - query(tme[in[m]-1], 1, N, in[1], in[par[j]]);
                ttt -= query(tme[out[i]], 1, N, in[1], in[par[j]]) - query(tme[in[i]-1], 1, N, in[1], in[par[j]]);
                if(!(par[i] == j || (j == 1 || ttt) || (sum - pos > 0))) {
                    ans++;
                    goto CONTINUE;
                    continue;
                }
            }

            continue;
            CONTINUE: 
            {
                anss.emplace_back(min(i, j), max(i, j));
                // cout << i << " " << j << "\n";
            }
        }
    }

    sort(anss.begin(), anss.end());
    for(auto [i, j] : anss) {
        // cout << i << " " << j << "\n";
    }

    cout << ans << "\n";
}