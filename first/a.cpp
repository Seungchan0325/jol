#include <bits/stdc++.h>

using namespace std;

int N;

int main()
{
    cin >> N;
    int len;
    cin >> len;
    string s;
    cin >> s;

    int ans = 0;
    int cnt = 0;
    for(int i = 0; i < len - 2; i+=2) {
        if(s[i] == 'I' && s[i+1] == 'O' && s[i+2] == 'I') {
            cnt += 1;
            if(cnt >= N) ans++;
        } else {
            cnt = 0;
        }
    }
    cnt = 0;
    for(int i = 1; i < len - 2; i+=2) {
        if(s[i] == 'I' && s[i+1] == 'O' && s[i+2] == 'I') {
            cnt += 1;
            if(cnt >= N) ans++;
        } else {
            cnt = 0;
        }
    }
    cout << ans;
}