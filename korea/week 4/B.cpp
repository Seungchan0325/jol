#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 10101;

ll N, M, T;
vector<tuple<int, ll, ll>> graph[MAXN];

double dijkstra(int start, int end, double x)
{
    vector<double> dist(N+1, INFINITY);
    priority_queue<pair<double, int>> pq;
    dist[start] = 0.0;
    pq.emplace(dist[start], start);
    while(!pq.empty()) {
        auto [d, a] = pq.top(); pq.pop();
        d = -d;
        if(d > dist[a]) continue;
        for(auto [b, l, v] : graph[a]) {
            double nd = d + (double)l/((double)v+x);
            if(nd < dist[b]) {
                dist[b] = nd;
                pq.emplace(-dist[b], b);
            }
        }
    }
    return dist[end];
}

int main()
{
    cin >> N >> M >> T;
    for(int i = 0; i < M; i++) {
        ll a, b, l, v;
        cin >> a >> b >> l >> v;
        graph[a].emplace_back(b, l, v);
        graph[b].emplace_back(a, l, v);
    }

    double lo = 0;
    double hi = 1e9;
    for(int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2;
        if(dijkstra(1, N, mid) < T) hi = mid;
        else lo = mid;
    }
    cout << setprecision(10) << fixed << lo << "\n";
}