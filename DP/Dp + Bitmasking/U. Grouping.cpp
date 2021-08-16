// https://atcoder.jp/contests/dp/tasks/dp_u

#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)x.size()

using namespace std;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n;cin>>n;
    int grid[n][n];
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    
    int dp[(1<<n)];
    memset(dp, 0, sizeof(dp));
    for(int mask = 0;mask<(1 << n);mask++){

        int value = 0;
        std::vector<int> v;
        for(int i = 0;i<n;i++){
            if(mask & (1ll << i)) v.push_back(i);
        }

        for(int i = 0;i<sz(v);i++){
            for(int j = i + 1;j<sz(v);j++){
                value += grid[v[i]][v[j]];
            }
        }

        dp[mask] = value;

        for(int submask = mask;submask;submask = (submask - 1) & mask){
            dp[mask] = max(dp[mask], dp[submask] + dp[mask ^ submask]);
        }
    }

    cout<<dp[(1<<n) - 1];

}
