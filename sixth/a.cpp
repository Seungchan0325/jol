#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin >> s;

    stack<int> st;
    for(int i = 0; i < s.size(); i++) {
        if('0' <= s[i] && s[i] <= '9') {
            st.emplace(0);
        } else {
            int mx = 0;
            mx = max(st.top(), mx); st.pop();
            mx = max(st.top(), mx); st.pop();
            st.push(mx + 1);
        }
    }

    cout << st.top();
}