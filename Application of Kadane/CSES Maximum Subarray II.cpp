//https://cses.fi/problemset/task/1644/

#include "bits/stdc++.h"
#define int long long

using namespace std;

const int inf = 1e18;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    int a, b; cin>>a>>b;
    std::vector<int> v(n), pref(n + 1);
    for(auto &x : v) cin>>x;

    for(int i = 0;i<n;i++) pref[i + 1] = v[i] + pref[i];
    multiset<int>m;
    int ans = -inf;
    for(int i = a;i<=n;i++){
        if(i > b) m.erase(m.find(pref[i - b - 1]));
        m.insert(pref[i - a]);
        ans = max(ans, pref[i] - *m.begin());
    }

    cout<<ans;

}
