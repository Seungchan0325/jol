#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

ll tree[4*MAXN], lazy[4*MAXN];

void propagate(ll start, ll end, ll index) {
    if(lazy[index]) {
        tree[index] += (end - start + 1) * lazy[index];
        if(start != end) {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }
}

void update(ll start, ll end, ll index, ll left, ll right, ll delta) {
    propagate(start, end, index);
    if(end < left || right < start) return;

    if(left <= start && end <= right) {
        tree[index] += (end - start + 1) * delta;
        if(start != end) {
            lazy[2*index] += delta;
            lazy[2*index+1] += delta;
        }
        return;
    }

    ll mid = (start + end) / 2;
    update(start, mid, 2*index, left, right, delta);
    update(mid+1, end, 2*index+1, left, right, delta);
    tree[index] = tree[2*index] + tree[2*index+1];
}

ll query(ll start, ll end, ll index, ll left, ll right) {
    propagate(start, end, index);
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];

    ll mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) + query(mid+1, end, 2*index+1, left, right);
}

ll cnt[26], cnt1[26], cnt2[26];
vector<ll> v[26];

int main()
{
    ll N;
    string s;
    cin >> N; 
    cin >> s;

    string a;
    string b;

    ll k = 0;
    ll sum = 0;

    for(ll i = 0; i < N; i++) {
        cnt1[s[i]-'a']++;
    }

    for(ll i = N; i < 2*N; i++) {
        cnt2[s[i]-'a']++;
    }

    for(ll i = N-1; i >= 0; i--) {
        if(cnt1[s[i]-'a'] > cnt2[s[i]-'a']) {
            cnt1[s[i]-'a']--;
            cnt2[s[i]-'a']++;
            sum += N - k - 1 - i;
            k++;
            b.push_back(s[i]);
        } else {
            a.push_back(s[i]);
        }
    }

    reverse(b.begin(), b.end());
    reverse(a.begin(), a.end());

    memset(cnt1, 0, sizeof(cnt1));
    memset(cnt2, 0, sizeof(cnt2));

    for(ll i = 0; i < N; i++) {
        cnt1[s[i]-'a']++;
    }

    for(ll i = N; i < 2*N; i++) {
        cnt2[s[i]-'a']++;
    }

    k = 0;
    for(ll i = N; i < 2*N; i++) {
        if(cnt1[s[i]-'a'] < cnt2[s[i]-'a']) {
            cnt1[s[i]-'a']++;
            cnt2[s[i]-'a']--;
            sum += i - (N + k);
            k++;
            a.push_back(s[i]);
        } else {
            b.push_back(s[i]);
        }
    }

    sum += k * k;
    
    for(ll i = 0; i < b.size(); i++) {
        v[b[i]-'a'].push_back(i);
    }

    for(ll i = 0; i < N; i++) {
        ll idx = v[a[i]-'a'][cnt[a[i]-'a']++];
        sum += idx + query(0, N-1, 1, idx, idx) - i;
        update(0, N-1, 1, 0, idx, 1);
    }
    cout << sum;
}